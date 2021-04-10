/*!*********************************************************************
\title	  Captain Stealth
\file     CaughtByCameraEvent.h
\author   Liew Ruiheng Rayner (100%)
\par      DP email: r.liew\@digipen.edu
\date     10/04/2021

\brief
		  Caught by camera event. Contains data such as the room number
		  that the event took place in.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
***********************************************************************/

#pragma once
#include "GameObject.h"
#include "MessageBus.h"
#include "SecurityCamera.h"

namespace StarBangBang
{
	struct CaughtByCameraEvent
	{
		GameObject* gameObject;
		AEVec2 pos;
		unsigned int roomNum = 0;

		/*!*********************************************************************
		\brief
			Sends event to the message bus for listeners to respond
		***********************************************************************/
		void SendEvent()
		{
			roomNum = gameObject->GetComponent<SecurityCamera>()->GetRoomNum();
			Event e;
			e.id = EventId::CAUGHT_BY_CAMERA;
			e.context = *this;
			MessageBus::Notify(e);
		};
	};
}