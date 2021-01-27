#pragma once
#include "ScriptComponent.h"

namespace StarBangBang
{
	class PrimaryMovementController : public Script
	{
	public:
		PrimaryMovementController(GameObject* gameObject);
		_Component* Clone(GameObject* obj, _Component*) { return new PrimaryMovementController(obj); };
		void Start();
		void Update();
		int doodoo;
	};
}