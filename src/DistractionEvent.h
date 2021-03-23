#pragma once
#include "GameObject.h"
#include "MessageBus.h"

namespace StarBangBang
{
	struct DistractionEvent
	{
		GameObject* gameObject;

		void SendEvent()
		{
			Event e;
			e.id = EventId::DISTRACTION;
			e.context = *this;
			MessageBus::Notify(e);
		};

	};
}