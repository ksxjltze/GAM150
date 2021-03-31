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