/******************************************************************************/
/*!
\title		Captain Stealth
\file		PrimaryMovementController.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Primary Movement Controller script.
			Allows the gameObject to move around with WASD and Arrow keys.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "ScriptComponent.h"
#include "Physics.h"

namespace StarBangBang
{
	class PrimaryMovementController : public Script
	{
	public:
		PrimaryMovementController(GameObject* gameObject);
		void Start();
		void Update();
	private:
		StarBangBang::RigidBody* rb;
	};
}