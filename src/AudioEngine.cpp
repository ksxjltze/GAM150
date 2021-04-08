#include "AudioEngine.h"
#include "SoundEvent.h"
#include "MusicEvent.h"

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

void StarBangBang::AudioEngine::CreateSound(FMOD::Sound** sound, const std::string& file)
{
	CreateSound(sound, file.c_str());
}

void StarBangBang::AudioEngine::CreateSound(FMOD::Sound** sound, const char* file)
{
	system->createSound(file, FMOD_DEFAULT, 0, sound);
}

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
			std::cout << "Playing sound: " << musicEvent.name << std::endl;
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

void StarBangBang::AudioEngine::AddSound(const std::string& name, FMOD::Sound* sound)
{
	soundList.push_back({name, sound});
}

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

void StarBangBang::AudioEngine::ReleaseSound(FMOD::Sound* sound)
{
	sound->release();
}

void StarBangBang::AudioEngine::StopMasterChannel()
{
	FMOD::ChannelGroup* channelGroup;
	system->getMasterChannelGroup(&channelGroup);
	channelGroup->stop();
}

void StarBangBang::AudioEngine::Update()
{
	system->update();
}

void StarBangBang::AudioEngine::Mute(ChannelGroupId cgId)
{
	FMOD::ChannelGroup* channelGroup;
	channelGroup = channelGroupMap.at(cgId);

	bool muted;
	channelGroup->getMute(&muted);
	channelGroup->setMute(!muted);
}

void StarBangBang::AudioEngine::Exit()
{
	system->close();
}
