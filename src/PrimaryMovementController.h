#pragma once
#include "ScriptComponent.h"

namespace StarBangBang
{
	class PrimaryMovementController : public Script
	{
	public:
		PrimaryMovementController(GameObject* gameObject);
		Component* Clone(GameObject* obj, Component*) { return new PrimaryMovementController(obj); };
		void Start();
		void Update();
		int doodoo;
	};
}