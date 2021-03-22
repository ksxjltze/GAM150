#pragma once
#include "ScriptComponent.h"
#include "PrimaryMovementController.h"
#include "CameraComponent.h"

namespace StarBangBang
{
	class MovementManager : public Script
	{
	public:
		MovementManager(GameObject* obj) : Script(obj), cam{ nullptr }, controllerId{ 0 }{}
		void AddController(GameObject* obj);
		void Start();
		void Update();
		void SetActiveController(int id);
		void SetActiveController(GameObject* obj);
		void SetCamera(GameObject* obj);
	private:
		std::vector<PrimaryMovementController*> controllers;
		int controllerId;
		CameraComponent* cam;
	};
}