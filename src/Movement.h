/******************************************************************************/
/*!
\title		Captain Stealth
\file		Movement.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Movement script.
			Directly translates the game object using WASD.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "ScriptComponent.h"

namespace StarBangBang
{
	class Movement : public Script
	{
	public:
		/*!*************************************************************************
		 * \brief 
		 * Script Constructor.
		 * Attaches the script to a game object
		 * \param gameObject
		 * GameObject to attach to.
		***************************************************************************/
		Movement(GameObject* gameObject);

		/*!*************************************************************************
		 * \brief 
		 * Start function. Called once at the start of the scene.
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
	};
}