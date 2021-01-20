#pragma once
#include "GameObject.h"

namespace StarBangBang
{
	class Component
	{
	public:
		Component(GameObject* gameObject, int componentId) { this->gameObject = gameObject; id = componentId; }
		inline GameObject* GetGameObject() { return gameObject; }
		virtual void Update() {};
		int id { 0 };
		GameObject* gameObject { nullptr };
	};
}