#pragma once
#include "GameObject.h"
#include "constants.h"

namespace StarBangBang
{
	class Component
	{
	public:
		Component(GameObject* gameObject) { this->gameObject = gameObject; }
		inline virtual Component* Clone(GameObject* obj, Component* component) 
		{ 
			//TO DEPRECATE (force abstract)
			return new Component(obj);
		}
		virtual void Update() {};
		GameObject* gameObject { nullptr };
		virtual ~Component() {}
	};
}