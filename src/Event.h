/******************************************************************************/
/*!
\title		Captain Stealth
\file		Event.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Event class.
			Contains an event ID and a context.

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/

#pragma once
#include <any>
#include <iostream>

enum class EventId 
{ 
	DISAPPEAR,
	DISTRACTION, 
	COMPUTER_CLICK, 
	DETECTED, 
	PLAY_SOUND, 
	PLAY_MUSIC, 
	STOP_SOUND,
	PAUSE_MUSIC,
	MUTE,
	TEST, 
	PRINT_TEXT, 
	COLLISION, 
	PLAYER_COLLISION,
	CAUGHT_BY_CAMERA,
	GAME_OVER
};

namespace StarBangBang
{
	struct Event
	{
		EventId id{ -1 };
		std::any context;
	};
}