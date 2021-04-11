/******************************************************************************/
/*!
\title		Captain Stealth
\file		AudioEngine.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat@digipen.edu
\date   	April 09, 2021
\brief		AudioEngine class.
			Plays audio using the fmod API.

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/

#pragma once
#pragma warning(push)
#pragma warning(disable : 26812)
#include "fmod.hpp"
#pragma warning(pop)

#include "Listener.h"
#include <vector>
#include <string>
#include <map>
#include "constants.h"

namespace StarBangBang
{
	struct Sound
	{
		std::string name;
		FMOD::Sound* sound;
	};

	class AudioEngine : public Listener
	{
	public:
		/*!*************************************************************************
		 * \brief 
		 * Audio Engine constructor. 
		 * Initializes the fmod Audio System and creates the channel groups for use.
		***************************************************************************/
		AudioEngine();

		/*!*************************************************************************
		 * \brief 
		 * Creates a sound from the provided file path.
		 * \param sound 
		 * Output Pointer to a Pointer of the sound object.
		 * \param file 
		 * C style string to the file path of the sound.
		***************************************************************************/
		void CreateSound(FMOD::Sound** sound, const char* file);

		/*!*************************************************************************
		 * \brief 
		 * Creates a sound from the provided file path..
		 * \param sound
		 * Output Pointer to a Pointer of the sound object.
		 * \param 
		 * string to the file path of the sound.
		***************************************************************************/
		void CreateSound(FMOD::Sound** sound, const std::string&);

		/*!*************************************************************************
		 * \brief
		 * Listener callback. Invoked when an event is received from the Message Bus.
		 * Listens for events: PLAY_SOUND, PLAY_MUSIC, STOP_SOUND and MUTE
		 * \param e Event data.
		***************************************************************************/
		void onNotify(Event e);

		/*!*************************************************************************
		 * \brief 
		 * Maps a sound object to a specified name.
		 * \param name
		 * Name to map to.
		 * \param sound
		 * Pointer to the sound object to map.
		***************************************************************************/
		void AddSound(const std::string& name, FMOD::Sound* sound);

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
		void playSound(FMOD::Sound* sound, bool loop = false, ChannelGroupId cgId = ChannelGroupId::SFX);

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
		void playSound(const std::string& name, bool loop = false, ChannelGroupId cgId = ChannelGroupId::SFX);

		/*!*************************************************************************
		 * \brief 
		 * Releases a sound object, freeing the allocated memory.
		 * \param sound
		 * Pointer to the sound object to free.
		***************************************************************************/
		void ReleaseSound(FMOD::Sound* sound);

		/*!*************************************************************************
		 * \brief 
		 * Stops the master channel.
		***************************************************************************/
		void StopMasterChannel();

		/*!*************************************************************************
		 * \brief 
		 * Update function. Called once per frame.
		***************************************************************************/
		void Update();

		/*!*************************************************************************
		 * \brief 
		 * Mutes a channel group.
		 * \param cgId
		 * Channel Group Id
		***************************************************************************/
		void Mute(ChannelGroupId cgId);

		/*!*************************************************************************
		 * \brief 
		 * Closes the sound system.
		***************************************************************************/
		void Exit();
	private:
		bool paused{ false };
		FMOD::System* system;
		std::map<ChannelGroupId, FMOD::ChannelGroup*> channelGroupMap;
		std::vector<Sound> soundList;
	};
}