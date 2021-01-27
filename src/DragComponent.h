#pragma once
#include "Component.h"

//Change to script
namespace StarBangBang
{
	class DragComponent : public _Component
	{
	public:
		DragComponent(GameObject* gameObject);
		_Component* Clone(GameObject* gameObject, _Component* component);
		void Update();
	private:
		bool enabled;
	};
}