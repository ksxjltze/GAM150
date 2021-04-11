/******************************************************************************/
/*!
\title		Captain Stealth
\file		DistractionEvent.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Distraction Event.
			Contains data for distraction, such as the duration of the distraction,
			its room number and the game object that is doing the distracting.

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All rights reserved.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "GameObject.h"
#include "Collider.h"
#include "MessageBus.h"

namespace StarBangBang
{
	struct CollisionEvent
	{
		Collider* first;
		Collider* second;

		/*!*************************************************************************
		 * \brief 
		 * Sends a collision event to the message bus.
		 * \return
		 * void
		***************************************************************************/
		void SendEvent() 
		{ 
			Event e;
			e.id = EventId::COLLISION;
			e.context = *this;
			MessageBus::Notify(e); 
		};

	};
}