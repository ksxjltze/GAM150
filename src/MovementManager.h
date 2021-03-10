#pragma once
#include "ScriptComponent.h"
#include "PrimaryMovementController.h"

namespace StarBangBang
{
	class MovementManager : public Script
	{
	public:
		MovementManager(GameObject* obj) : Script(obj) {}
		void AddController(GameObject* obj);
		void Start();
		void Update();
		void SetActiveController(int id);
	private:
		std::vector<PrimaryMovementController*> controllers;
	};
}