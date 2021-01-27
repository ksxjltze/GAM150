#pragma once
#include "GameObject.h"
#include "constants.h"
#include "BusNode.h"

namespace StarBangBang
{
	class Component : BusNode
	{
	public:
		Component(GameObject* gameObject) { this->gameObject = gameObject; }
		inline virtual Component* Clone(GameObject* obj, Component* component) { return new Component(obj); }
		virtual void Update() {};
		GameObject* gameObject { nullptr };
		virtual ~Component() {}
	};
}