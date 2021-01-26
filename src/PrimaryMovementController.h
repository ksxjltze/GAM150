#pragma once
#include "ScriptComponent.h"

namespace StarBangBang
{
	class PrimaryMovementController : public Script
	{
	public:
		PrimaryMovementController(GameObject* gameObject);
		Component* Clone(Component* component) { return new PrimaryMovementController(component->gameObject); };
		void Start();
		void Update();
		int doodoo;
	};
}