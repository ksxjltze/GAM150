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

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/


#pragma once
#include "GameObject.h"
#include "MessageBus.h"
#include "Distractor.h"

namespace StarBangBang
{
	struct DistractionEvent
	{
		GameObject* gameObject;
		unsigned int roomNum = 0;
		float duration;

		/*!*************************************************************************
		 * \brief 
		 * Sends a distraction event to the message bus.
		 * \return
		 * void
		***************************************************************************/
		void SendEvent()
		{
			roomNum = gameObject->GetComponent<Distractor>()->GetRoomNum();
			duration = gameObject->GetComponent<Distractor>()->GetDuration();
			Event e;
			e.id = EventId::DISTRACTION;
			e.context = *this;
			MessageBus::Notify(e);
		};

	};
}