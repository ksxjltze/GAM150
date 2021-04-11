/******************************************************************************/
/*!
\title		Captain Stealth
\file		MovementManager.cpp
\author 	Lee Jia Keat
\par    	email: l.jiakeat@digipen.edu
\date   	April 09, 2021
\brief		Movement Manager script.
			Manages movement controllers, allowing toggling between them.

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/
#include "MovementManager.h"
#include "CameraComponent.h"

/*!*************************************************************************
 * \brief
 * Gets the Movement controller script of the game object and adds it to the list.
 * \param obj GameObject to register.
 * \return
 * void
***************************************************************************/
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

/*!*************************************************************************
 * \brief
 * Start function. Called once at the start of the scene.
 * Resets all active controllers.
 * \return
 * void
***************************************************************************/
void StarBangBang::MovementManager::Start()
{
	controllerId = 0;
	SetActiveController(controllerId);
}

/*!*************************************************************************
 * \brief
 * Update function. Called once per frame.
 * \return
 * void
***************************************************************************/
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

/*!*************************************************************************
 * \brief
 * Sets the camera target.
 * \param obj
 * Game object to set target to.
***************************************************************************/
void StarBangBang::MovementManager::SetCamera(GameObject* obj)
{
	CameraComponent* camera = obj->GetComponent<CameraComponent>();
	if (camera)
		cam = camera;
}

/*!*************************************************************************
 * \brief
 * Sets the active movement controller.
 * \param id
 * Id of the controller.
***************************************************************************/
void StarBangBang::MovementManager::SetActiveController(int id)
{
	if (controllers.size() == 0)
		return;

	SetActiveController(controllers.at(id)->gameObject);
}

/*!*************************************************************************
 * \brief
 * Gets the active controller.
 * \return
 * GameObject that has the active controller.
***************************************************************************/
StarBangBang::GameObject* StarBangBang::MovementManager::GetActiveController()
{
	return activeCharacter;
}

/*!*************************************************************************
 * \brief
 * Sets the active controller.
 * Gets the MovementController from the specified game object.
 * \param obj
 * GameObject to set.
***************************************************************************/
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

/*!*************************************************************************
 * \brief
 * Removes a movement controller.
 * \param obj
 * GameObject pointer to find.
***************************************************************************/
void StarBangBang::MovementManager::RemoveController(GameObject* obj)
{
	for (auto it = controllers.begin(); it != controllers.end(); ++it)
	{
		if ((*it)->gameObject == obj)
		{
			(*it)->active = false;
			controllers.erase(it);

			if (!controllers.empty())
				SetActiveController(controllers.front()->gameObject);
			return;
		}
	}
}
