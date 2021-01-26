#pragma once
#include "ScriptComponent.h"
#include "PrimaryMovementController.h"
#include "SecondaryMovementController.h"

namespace StarBangBang
{
	class Player : public Script
	{
	public:
		Player(GameObject* gameObject);
		Component* Clone(GameObject* obj, Component* base) { return new Player(obj); }
		void Load();
		void Start();
		void Update();
	private:
		PrimaryMovementController movementController {gameObject};
		SecondaryMovementController secondaryMovementController {gameObject};
	};
}

