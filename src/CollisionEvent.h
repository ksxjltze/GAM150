/******************************************************************************/
/*!
\title		Captain Stealth
\file		CollisionEvent.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Collision Event.
			Contains data for collision, such as the colliders.

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
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