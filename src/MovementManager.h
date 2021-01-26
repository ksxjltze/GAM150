#pragma once
#include "ScriptComponent.h"
#include "PrimaryMovementController.h"

namespace StarBangBang
{
	class MovementManager : public Script
	{
	public:
		MovementManager(GameObject* obj) : Script(obj) {}
		Component* Clone(GameObject* obj, Component*) { return new MovementManager(obj); };
		void AddController(GameObject* obj);
		void Start();
		void Update();
	private:
		void SetActiveController(int id);
		std::vector<PrimaryMovementController*> controllers;
	};
}