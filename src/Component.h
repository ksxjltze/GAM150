#pragma once
#include "GameObject.h"
#include "constants.h"

namespace StarBangBang
{
	class Component
	{
	public:
		Component(GameObject* gameObject, int componentId) { this->gameObject = gameObject; id = componentId; }
		inline GameObject* GetGameObject() { return gameObject; }
		inline virtual Component* Clone(GameObject* obj, Component* component = nullptr) 
		{ 
			if (component->id != id)
				return nullptr;

			return new Component(obj, component->id);
		}
		virtual void Update() {};
		int id { Constants::ComponentType::NONE };
		GameObject* gameObject { nullptr };
		Component() {}
		virtual ~Component() {}
	};
}