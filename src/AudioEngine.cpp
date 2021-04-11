/******************************************************************************/
/*!
\title		Captain Stealth
\file		AudioEngine.cpp
\author 	Lee Jia Keat
\par    	email: l.jiakeat@digipen.edu
\date   	April 09, 2021
\brief		AudioEngine class.
			Plays audio using the fmod API.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#include "AudioEngine.h"
#include "SoundEvent.h"
#include "MusicEvent.h"

/*!*************************************************************************
* \brief
* Audio Engine constructor.
* Initializes the fmod Audio System and creates the channel groups for use.
***************************************************************************/
StarBangBang::AudioEngine::AudioEngine()
{
	if (FMOD::System_Create(&system) != FMOD_OK)
	{
		//Report some error
		return;
	}

	int driverCount = 0;
	system->getNumDrivers(&driverCount);

	if (driverCount == 0)
	{
		//Report some error
		return;
	}

	system->init(36, FMOD_INIT_NORMAL, 0);

	FMOD::ChannelGroup* channelGroupBGM;
	FMOD::ChannelGroup* channelGroupSFX;
	system->createChannelGroup("BGM", &channelGroupBGM);
	system->createChannelGroup("SFX", &channelGroupSFX);
	channelGroupMap.insert({ ChannelGroupId::BGM, channelGroupBGM });
	channelGroupMap.insert({ ChannelGroupId::SFX, channelGroupSFX });

}

/*!*************************************************************************
 * \brief
 * Creates a sound from the provided file path.
 * \param sound
 * Output Pointer to a Pointer of the sound object.
 * \param file
 * C style string to the file path of the sound.
***************************************************************************/
void StarBangBang::AudioEngine::CreateSound(FMOD::Sound** sound, const std::string& file)
{
	CreateSound(sound, file.c_str());
}

/*!*************************************************************************
 * \brief
 * Creates a sound from the provided file path..
 * \param sound
 * Output Pointer to a Pointer of the sound object.
 * \param
 * string to the file path of the sound.
***************************************************************************/
void StarBangBang::AudioEngine::CreateSound(FMOD::Sound** sound, const char* file)
{
	system->createSound(file, FMOD_DEFAULT, 0, sound);
}


/*!*************************************************************************
 * \brief
 * Listener callback. Invoked when an event is received from the Message Bus.
 * Listens for events: PLAY_SOUND, PLAY_MUSIC, STOP_SOUND and MUTE
 * \param e Event data.
***************************************************************************/
void StarBangBang::AudioEngine::onNotify(Event e)
{
	if (e.id == EventId::PLAY_SOUND)
	{
		try
		{
			SoundEvent soundEvent = std::any_cast<SoundEvent>(e.context);
			std::cout << "Playing sound: " << soundEvent.name << std::endl;
			playSound(soundEvent.name, false, ChannelGroupId::SFX);
		}
		catch (const std::exception&)
		{
			std::cout << "ERROR PLAYING SOUND" << std::endl;
			return;
		}

	}
	else if (e.id == EventId::PLAY_MUSIC)
	{
		try
		{
			MusicEvent musicEvent = std::any_cast<MusicEvent>(e.context);
			std::cout << "Playing music: " << musicEvent.name << std::endl;
			playSound(musicEvent.name, musicEvent.loop, ChannelGroupId::BGM);
		}
		catch (const std::exception&)
		{
			std::cout << "ERROR PLAYING SOUND" << std::endl;
			return;
		}

	}

	if (e.id == EventId::STOP_SOUND)
	{
		StopMasterChannel();
	}
	else if (e.id == EventId::PAUSE_MUSIC)
	{
		paused = std::any_cast<bool>(e.context);
		channelGroupMap.at(ChannelGroupId::BGM)->setPaused(paused);
	}

	if (e.id == EventId::MUTE)
	{
		ChannelGroupId cgId = std::any_cast<ChannelGroupId>(e.context);
		if (cgId == ChannelGroupId::ALL)
		{
			for (const auto& cgPair : channelGroupMap)
			{
				Mute(cgPair.first);
			}
		}
		else
			Mute(cgId);
	}

}

/*!*************************************************************************
 * \brief
 * Maps a sound object to a specified name.
 * \param name
 * Name to map to.
 * \param sound
 * Pointer to the sound object to map.
***************************************************************************/
void StarBangBang::AudioEngine::AddSound(const std::string& name, FMOD::Sound* sound)
{
	soundList.push_back({name, sound});
}

/*!*************************************************************************
 * \brief
 * Plays a sound.
 * \param sound
 * Pointer to the sound object to play.
 * \param loop
 * True to loop, false to play once
 * \param cgId
 * Channel Group Id
***************************************************************************/
void StarBangBang::AudioEngine::playSound(FMOD::Sound* sound, bool loop, ChannelGroupId cgId)
{
	if (!loop)
	{
		sound->setMode(FMOD_LOOP_OFF);
	}
	else
	{
		sound->setMode(FMOD_LOOP_NORMAL);
		sound->setLoopCount(-1);
	}
	FMOD::Channel* channel;
	FMOD::ChannelGroup* channelGroup;

	channelGroup = channelGroupMap.at(cgId);
	system->getChannel(0, &channel);
	channel->setChannelGroup(channelGroup);
	system->playSound(sound, channelGroup, false, &channel);
}

/*!*************************************************************************
 * \brief
 * Plays a sound by name.
 * \param name
 * Name of the sound object.
 * \param loop
 * True to loop, false to play once
 * \param cgId
 * Channel Group Id
***************************************************************************/
void StarBangBang::AudioEngine::playSound(const std::string& name, bool loop, ChannelGroupId cgId)
{
	for (auto sound : soundList)
	{
		if (sound.name == name)
		{
			playSound(sound.sound, loop, cgId);
		}
	}
}

/*!*************************************************************************
 * \brief
 * Releases a sound object, freeing the allocated memory.
 * \param sound
 * Pointer to the sound object to free.
***************************************************************************/
void StarBangBang::AudioEngine::ReleaseSound(FMOD::Sound* sound)
{
	sound->release();
}

/*!*************************************************************************
 * \brief
 * Stops the master channel.
***************************************************************************/
void StarBangBang::AudioEngine::StopMasterChannel()
{
	FMOD::ChannelGroup* channelGroup;
	system->getMasterChannelGroup(&channelGroup);
	channelGroup->stop();
}

/*!*************************************************************************
 * \brief
 * Update function. Called once per frame.
***************************************************************************/
void StarBangBang::AudioEngine::Update()
{
	system->update();
}

/*!*************************************************************************
 * \brief
 * Mutes a channel group.
 * \param cgId
 * Channel Group Id
***************************************************************************/
void StarBangBang::AudioEngine::Mute(ChannelGroupId cgId)
{
	FMOD::ChannelGroup* channelGroup;
	channelGroup = channelGroupMap.at(cgId);

	bool muted;
	channelGroup->getMute(&muted);
	channelGroup->setMute(!muted);
}

/*!*************************************************************************
 * \brief
 * Closes the sound system.
***************************************************************************/
void StarBangBang::AudioEngine::Exit()
{
	system->close();
}
