/******************************************************************************/
/*!
\title		Captain Stealth
\file		SoundEvent.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Sound Event.
			Contains data for playing sound effects.

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/

#pragma once
#include <string>
#include "MessageBus.h"

namespace StarBangBang
{
	struct SoundEvent
	{
		const std::string name;
		float volume;

		SoundEvent(const std::string& name, float volume = 1.0f) : name{ name }, volume{ volume }
		{

		}

		void SendEvent()
		{
			Event e{ EventId::PLAY_SOUND, *this };
			MessageBus::Notify(e);
		};
	};
}