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
		SetCamera(obj);
	}
}

void StarBangBang::MovementManager::Start()
{
	controllerId = 0;
	SetActiveController(controllerId);
}

void StarBangBang::MovementManager::Update()
{
	if (!cam->GetTarget()->active)
	{
		for (auto controller : controllers)
		{
			if (controller->gameObject->active)
				SetActiveController(controller->gameObject);
		}
	}

	if (AEInputCheckTriggered(AEVK_TAB))
	{
		if (++controllerId >= controllers.size())
		{
			controllerId = 0;
		}

		SetActiveController(controllerId);
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

StarBangBang::GameObject* StarBangBang::MovementManager::GetActiveController()
{
	return activeCharacter;
}

void StarBangBang::MovementManager::SetActiveController(GameObject* obj)
{
	for (PrimaryMovementController* controller : controllers)
	{
		controller->SetActive(false);
	}
	obj->GetComponent<PrimaryMovementController>()->SetActive(true);
	activeCharacter = obj;

	if (cam)
		cam->SetTarget(obj);
}

void StarBangBang::MovementManager::RemoveController(GameObject* obj)
{
	for (auto it = controllers.begin(); it != controllers.end(); ++it)
	{
		if ((*it)->gameObject == obj)
		{
			(*it)->active = false;
			controllers.erase(it);
			SetActiveController(controllers.front()->gameObject);
			return;
		}
	}
}
