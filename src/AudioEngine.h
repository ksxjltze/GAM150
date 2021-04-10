/******************************************************************************/
/*!
\title		Captain Stealth
\file		AudioEngine.h
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
		AudioEngine();
		void CreateSound(FMOD::Sound** sound, const char* file);
		void CreateSound(FMOD::Sound** sound, const std::string&);
		void onNotify(Event e);
		void AddSound(const std::string& name, FMOD::Sound* sound);
		void playSound(FMOD::Sound* sound, bool loop = false, ChannelGroupId cgId = ChannelGroupId::SFX);
		void playSound(const std::string& name, bool loop = false, ChannelGroupId cgId = ChannelGroupId::SFX);
		void ReleaseSound(FMOD::Sound* sound);
		void StopMasterChannel();
		void Update();
		void Mute(ChannelGroupId cgId);
		void Exit();
	private:
		bool paused{ false };
		FMOD::System* system;
		std::map<ChannelGroupId, FMOD::ChannelGroup*> channelGroupMap;
		std::vector<Sound> soundList;
	};
}