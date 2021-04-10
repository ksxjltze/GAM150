/******************************************************************************/
/*!
\title		Captain Stealth
\file		MovementManager.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat@digipen.edu
\date   	April 09, 2021
\brief		Movement Manager script. 
			Manages movement controllers, allowing toggling between them.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
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
		MovementManager(GameObject* obj) : Script(obj), cam{ nullptr }, controllerId{ 0 }{}
		/*!*************************************************************************
		 * \brief
		 * Gets the Movement controller script of the game object and adds it to the list.
		 * \param obj GameObject to register.
		***************************************************************************/
		void AddController(GameObject* obj);
		void Start();
		void Update();
		void SetActiveController(int id);
		GameObject* GetActiveController();
		void SetActiveController(GameObject* obj);
		void RemoveController(GameObject* obj);
		void SetCamera(GameObject* obj);
	private:
		GameObject* activeCharacter{ nullptr };
		std::vector<PrimaryMovementController*> controllers;
		int controllerId;
		CameraComponent* cam;
	};
}