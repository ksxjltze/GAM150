#pragma once
#include "ScriptComponent.h"

namespace StarBangBang
{
	class PrimaryMovementController : public Script
	{
	public:
		PrimaryMovementController(GameObject* gameObject);
		void Start();
		void Update();
	};
}