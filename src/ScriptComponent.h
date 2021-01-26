#pragma once
#include "Component.h"
#include "Observer.h"

namespace StarBangBang
{
	class Script : public Component
	{
	public:
		inline Script(GameObject* gameObject) : Component(gameObject) {this->gameObject = gameObject;}
		virtual Component* Clone(GameObject* gameObject, Component* component) = 0;

		virtual void Start() {};
		virtual void Update() {};
	};
}