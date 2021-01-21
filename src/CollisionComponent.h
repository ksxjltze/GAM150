#pragma once
#include "Component.h"

namespace StarBangBang
{
	class CollisionComponent : public Component
	{
	public:
		CollisionComponent(GameObject* gameObject);
		const static int id = 4;
	};
}