#pragma once
#include "GameObject.h"
#include "Collider.h"

namespace StarBangBang
{
	struct CollisionEvent
	{
		GameObject* gameObject;
		std::pair<Collider*, Collider*> colliderPair;

	};
}