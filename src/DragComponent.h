#pragma once
#include "Component.h"

//Change to script
namespace StarBangBang
{
	class DragComponent : public Component
	{
	public:
		DragComponent(GameObject* gameObject);
		Component* Clone(GameObject* gameObject, Component* component);
		void Update();
	private:
		bool enabled;
	};
}