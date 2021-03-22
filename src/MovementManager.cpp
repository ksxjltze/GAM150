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

	//if (AEInputCheckTriggered(AEVK_1))
	//{
	//	std::cout << "Activating controller 1." << std::endl;
	//	SetActiveController(0);
	//}
	//else if (AEInputCheckTriggered(AEVK_2))
	//{
	//	std::cout << "Activating controller 2." << std::endl;
	//	SetActiveController(1);
	//}
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

	for (PrimaryMovementController* controller : controllers)
	{
		controller->SetActive(false);
	}

	PrimaryMovementController* controller = controllers.at(id);
	controller->SetActive(true);

	if (cam)
		cam->SetTarget(controller->gameObject);

}
