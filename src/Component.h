/******************************************************************************/
/*!
\title		Captain Stealth
\file		Component.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Component class. Is responsible for driving game behavior.
			Must be attached to a game object.

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/

#pragma once
#include "GameObject.h"
#include "constants.h"

namespace StarBangBang
{
	class ObjectManager;

	class GameComponent
	{
	public:
		/*!*************************************************************************
		 * \brief 
		 * Component Constructor.
		 * Attaches the component to a game object.
		 * \param gameObject
		 * GameObject to attach to.
		***************************************************************************/
		GameComponent(GameObject* gameObject) { this->gameObject = gameObject; }

		/*!*************************************************************************
		 * \brief 
		 * Clone function. Clones the component and attaches it to a new game object.
		 * \param obj
		 * GameObject to attach to.
		 * \param
		 * Pointer to the Original component
		 * \return 
		 * Pointer to the cloned component.
		***************************************************************************/
		virtual GameComponent* Clone(GameObject* obj, GameComponent*) const { return new GameComponent(obj); }

		/*!*************************************************************************
		 * \brief Virtual
		 * Start function. Called once at the start of the scene.
		***************************************************************************/
		virtual void Start() {};

		/*!*************************************************************************
		 * \brief Virtual
		 * Update function. Called once per frame.
		***************************************************************************/
		virtual void Update() {};

		/*!*************************************************************************
		 * \brief Virtual
		 * Draw function. Called once per frame.
		***************************************************************************/
		virtual void Draw() {};

		/*!*************************************************************************
		 * \brief Virtual
		 * LateUpdate function. Called once per frame after Update().
		***************************************************************************/
		virtual void LateUpdate() {};

		/*!*************************************************************************
		 * \brief Virtual
		 * Destructor.
		***************************************************************************/
		virtual ~GameComponent() {}

		GameObject* gameObject { nullptr };
		bool drawable{ false };
		bool active { true };
		ObjectManager* objMgr{ nullptr };

	};
}