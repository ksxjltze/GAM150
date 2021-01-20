#pragma once
#include "ScriptComponent.h"
#include "PrimaryMovementController.h"

namespace StarBangBang
{
	class Player : public Script
	{
	public:
		Player(GameObject* gameObject);
		void Load();
		void Start();
		void Update();
	private:
		PrimaryMovementController movementController {gameObject};
	};
}

