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
		inline virtual Component* Clone(GameObject* gameObject, Component* component) 
		{ 
			return new Component(gameObject, component->id);
		}
		virtual void Update() {};
		int id { Constants::ComponentType::NONE };
		GameObject* gameObject { nullptr };

		Component() {}
		~Component() {}
	};
}