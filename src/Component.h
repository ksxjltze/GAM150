#pragma once
#include "GameObject.h"
#include "constants.h"

namespace StarBangBang
{
	class Component
	{
	public:
		int id;
		Component() { id = Constants::ComponentType::NONE; };
		Component(GameObject* gameObject, int componentId = Constants::ComponentType::NONE) { this->gameObject = gameObject; id = componentId; }
		inline virtual Component* Clone(GameObject* obj, Component* component = nullptr) 
		{ 
			//TO DEPRECATE (force abstract)
			if (component->id != id)
				return nullptr;

			return new Component(obj, component->id);
		}
		virtual void Update() {};
		GameObject* gameObject { nullptr };
		virtual ~Component() {}
	};
}