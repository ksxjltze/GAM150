#pragma once
#include "ScriptComponent.h"

namespace StarBangBang
{
	class SecondaryMovementController : public Script
	{
	public:
		SecondaryMovementController(GameObject* gameObject) : Script(gameObject) {};
		void Start();
		void Update();
	private:
		AEVec2 velocity{ 0, 0 };
	};
}