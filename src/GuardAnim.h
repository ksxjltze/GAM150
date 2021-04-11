/*!*********************************************************************
\title	  Captain Stealth
\file     GuardAnim.h
\author   Sim Chin Hin
\par      DP email: s.chinhin\@digipen.edu
\date     11/04/2021

\brief
		  This file contains the GuardAnim script class

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
***********************************************************************/
#pragma once
#include "ScriptComponent.h"
#include "GraphicsManager.h"

namespace StarBangBang
{
	class RigidBody;
	class GuardMovement;
	enum class guard_direction;

	class GuardAnim : public Script
	{
	public:
		/*!*********************************************************************
		\brief
			 Non default constructor
		\param 
			gameObject
		***********************************************************************/
		GuardAnim(GameObject* gameObject);
		/*!*********************************************************************
		\brief
			 Initialising guard animations
		***********************************************************************/
		void Start();
		/*!*********************************************************************
		\brief
			 Update guard animations
		***********************************************************************/
		void Update();
		/*!*********************************************************************
		\brief
			 Load guard's sprites
		***********************************************************************/
		static void Load(GraphicsManager& gfxMgr);

	private:
		RigidBody* rb;
		GuardMovement* movement;

		guard_direction dir;
		float app_time = 0.0f;
		int animation_counter = 0;
	};
}

