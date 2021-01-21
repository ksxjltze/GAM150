#pragma once
#include "Component.h"

namespace StarBangBang
{
	class DragComponent : public Component
	{
	public:
		const static int id = Constants::ComponentType::DRAG;
		DragComponent(GameObject* gameObject);
		Component* Clone(GameObject* gameObject, Component* component);
		void Update();
	private:
		bool enabled;
	};
}