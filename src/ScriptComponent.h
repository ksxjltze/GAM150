#pragma once
#include "Component.h"

namespace StarBangBang
{
	class Script : public Component
	{
	public:
		const static int id = Constants::ComponentType::SCRIPT;
		inline Script(GameObject* gameObject) : Component(gameObject, id)
		{
			this->gameObject = gameObject;
		}

		Component* Clone(GameObject* gameObject, Component* component) 
		{
			return new Script(gameObject);
		};

		virtual void Start() {};
		virtual void Update() {};
	};
}