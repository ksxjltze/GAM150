#pragma once
#include "Component.h"

namespace StarBangBang
{
	class CameraComponent : public Component
	{
	public:
		const static int id = Constants::ComponentType::CAMERA;
		CameraComponent(GameObject* gameObject);
		Component* Clone(GameObject* gameObject, Component* component);
		void Update();
		AEVec2 position;
	};
}