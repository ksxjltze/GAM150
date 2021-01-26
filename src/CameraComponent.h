#pragma once
#include "Component.h"

namespace StarBangBang
{
	class CameraComponent : public Component
	{
	public:
		CameraComponent(GameObject* gameObject);
		Component* Clone(GameObject* gameObject, Component* component);
		void Update();
		AEVec2 position;
	};
}