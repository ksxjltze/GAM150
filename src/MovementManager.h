#pragma once
#include "ScriptComponent.h"
#include "PrimaryMovementController.h"
#include "CameraComponent.h"

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
		void SetCamera(GameObject* obj);
	private:
		std::vector<PrimaryMovementController*> controllers;
		CameraComponent* cam;
	};
}