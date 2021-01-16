#pragma once
#include "Component.h"

namespace StarBangBang
{
	class TransformComponent : public Component
	{
	public:
		TransformComponent(GameObject* gameObject);
		GameObject* gameObject;
		AEVec2 position;
	};
}