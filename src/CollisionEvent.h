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

		void SendEvent() 
		{ 
			Event e;
			e.id = EventId::COLLISION;
			e.context = *this;
			MessageBus::Notify(e); 
		};

	};
}