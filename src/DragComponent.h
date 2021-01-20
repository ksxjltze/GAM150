#pragma once
#include "Component.h"

namespace StarBangBang
{
	class DragComponent : public Component
	{
	public:
		DragComponent(GameObject* gameObject);
		Component* clone(GameObject* gameObject, Component* component);
		void Update();
		const static int id = 2;
	private:
		bool enabled;
	};
}