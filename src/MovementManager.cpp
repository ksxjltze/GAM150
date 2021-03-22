#include "MovementManager.h"
#include <iostream>
#include "CameraComponent.h"

void StarBangBang::MovementManager::AddController(GameObject* obj)
{
	//Movement* controller = obj->GetComponent<Movement>();
	PrimaryMovementController* controller = obj->GetComponent<PrimaryMovementController>();
	if (controller != nullptr)
	{
		controllers.push_back(controller);
		controller->SetActive(false);
	}
	SetCamera(obj);
}

void StarBangBang::MovementManager::Start()
{
	SetActiveController(0);
}

void StarBangBang::MovementManager::Update()
{
	if (!cam->gameObject->active)
	{
		for (auto controller : controllers)
		{
			if (controller->gameObject->active)
				SetActiveController(controller->gameObject);
		}
	}

	if (AEInputCheckTriggered(AEVK_TAB))
	{
		static int id = 0;
		if (++id >= controllers.size())
		{
			id = 0;
		}

		SetActiveController(id);
	}
	else if (AEInputCheckTriggered(AEVK_SPACE))
	{
		SetActiveController(0);
	}

}

void StarBangBang::MovementManager::SetCamera(GameObject* obj)
{
	CameraComponent* camera = obj->GetComponent<CameraComponent>();
	if (camera)
		cam = camera;
}

void StarBangBang::MovementManager::SetActiveController(int id)
{
	if (controllers.size() == 0)
		return;

	SetActiveController(controllers.at(id)->gameObject);

}

void StarBangBang::MovementManager::SetActiveController(GameObject* obj)
{
	for (PrimaryMovementController* controller : controllers)
	{
		controller->SetActive(false);
	}
	obj->GetComponent<PrimaryMovementController>()->SetActive(true);

	if (cam)
		cam->SetTarget(obj);
}
