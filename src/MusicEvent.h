/******************************************************************************/
/*!
\title		Captain Stealth
\file		MusicEvent.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat@digipen.edu
\date   	April 09, 2021
\brief		Music Event.
			Contains data for playing music.

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/

#pragma once
#include <string>
#include "MessageBus.h"

namespace StarBangBang
{
	struct MusicEvent
	{
		const std::string name;
		float volume;
		bool loop;

		MusicEvent(const std::string& name, float volume = 1.0f, bool loop = true) : name{ name }, volume{ volume }, loop{loop}
		{

		}

		void SendEvent()
		{
			Event e{ EventId::PLAY_MUSIC, *this };
			MessageBus::Notify(e);
		};
	};
}