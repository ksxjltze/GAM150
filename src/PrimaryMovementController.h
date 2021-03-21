#pragma once
#include "ScriptComponent.h"
#include "Physics.h"

namespace StarBangBang
{
	class PrimaryMovementController : public Script
	{
	public:
		PrimaryMovementController(GameObject* gameObject);
		void Start();
		void Update();
	private:
		StarBangBang::RigidBody* rb;
	};
}