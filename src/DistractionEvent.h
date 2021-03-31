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

		void SendEvent()
		{
			roomNum = gameObject->GetComponent<Distractor>()->GetRoomNum();
			Event e;
			e.id = EventId::DISTRACTION;
			e.context = *this;
			MessageBus::Notify(e);
		};

	};
}