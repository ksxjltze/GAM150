/******************************************************************************/
/*!
\title		Captain Stealth
\file		Listener.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat@digipen.edu
\date   	April 09, 2021
\brief		Listener Interface (kinda).
			Can be inherited to listen for events from the Message Bus.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "Event.h"
#include "MessageBus.h"

namespace StarBangBang
{
	class Listener
	{
	public:
		Listener() : open{ true } { MessageBus::RegisterListener(this); };
		virtual void onNotify(Event e) = 0;
		inline bool isOpen() { return open; };
	protected:
		bool open;
	};
}