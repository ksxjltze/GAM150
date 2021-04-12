/******************************************************************************/
/*!
\title		Captain Stealth
\file		PrimaryMovementController.h
\author 	Lee Jia Keat
			Created the file and setup input flow.
\par    	email: l.jiakeat\@digipen.edu

\author2	Ho Yi Guan
			Integrated RigidBody mechanics.
\par		email: yiguan.ho@digipen.edu

\date   	April 09, 2021
\brief		Primary Movement Controller script.
			Allows the gameObject to move around with WASD and Arrow keys.

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
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
		/*!*************************************************************************
		 * \brief 
		 * Script constructor.
		 * Attaches the script to a game object
		 * \param gameObject
		 * GameObject to attach to.
		***************************************************************************/
		PrimaryMovementController(GameObject* gameObject);

		/*!*************************************************************************
		 * \brief 
		 * Start.
		 * \return
		 * void
		***************************************************************************/
		void Start();

		/*!*************************************************************************
		 * \brief
		 * Update.
		 * \return
		 * void
		***************************************************************************/
		void Update();
	private:
		StarBangBang::RigidBody* rb;
	};
}