#pragma once
#include "GameObject.h"
#include "Collider.h"
#include "MessageBus.h"

namespace StarBangBang
{
	struct CollisionEvent
	{
		GameObject* gameObject;
		std::pair<Collider*, Collider*> colliderPair;

		void SendEvent() { MessageBus::Notify({ EventId::COLLISION, *this }); };

	};
}