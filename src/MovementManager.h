/******************************************************************************/
/*!
\title		Captain Stealth
\file		MovementManager.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat@digipen.edu
\date   	April 09, 2021
\brief		Movement Manager script. 
			Manages movement controllers, allowing toggling between them.

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/

#pragma once
#include "ScriptComponent.h"
#include "PrimaryMovementController.h"
#include "CameraComponent.h"

namespace StarBangBang
{
	class MovementManager : public Script
	{
	public:
		/*!*************************************************************************
		 * \brief 
		 * Script constructor.
		 * Attaches the script to a game object.
		 * \param obj
		 * GameObject to attach to.
		***************************************************************************/
		MovementManager(GameObject* obj) : Script(obj), cam{ nullptr }, controllerId{ 0 }{}

		/*!*************************************************************************
		 * \brief
		 * Gets the Movement controller script of the game object and adds it to the list.
		 * \param obj GameObject to register.
		 * \return
		 * void
		***************************************************************************/
		void AddController(GameObject* obj);

		/*!*************************************************************************
		 * \brief 
		 * Start function. Called once at the start of the scene.
		 * Resets all active controllers.
		 * \return
		 * void
		***************************************************************************/
		void Start();

		/*!*************************************************************************
		 * \brief 
		 * Update function. Called once per frame.
		 * \return
		 * void
		***************************************************************************/
		void Update();

		/*!*************************************************************************
		 * \brief 
		 * Sets the active movement controller.
		 * \param id
		 * Id of the controller.
		***************************************************************************/
		void SetActiveController(int id);

		/*!*************************************************************************
		 * \brief 
		 * Gets the active controller.
		 * \return 
		 * GameObject that has the active controller.
		***************************************************************************/
		GameObject* GetActiveController();

		/*!*************************************************************************
		 * \brief 
		 * Sets the active controller.
		 * Gets the MovementController from the specified game object.
		 * \param obj
		 * GameObject to set.
		***************************************************************************/
		void SetActiveController(GameObject* obj);

		/*!*************************************************************************
		 * \brief 
		 * Removes a movement controller.
		 * \param obj
		 * GameObject pointer to find.
		***************************************************************************/
		void RemoveController(GameObject* obj);

		/*!*************************************************************************
		 * \brief 
		 * Sets the camera target.
		 * \param obj
		 * Game object to set target to.
		***************************************************************************/
		void SetCamera(GameObject* obj);
	private:
		GameObject* activeCharacter{ nullptr };
		std::vector<PrimaryMovementController*> controllers;
		int controllerId;
		CameraComponent* cam;
	};
}