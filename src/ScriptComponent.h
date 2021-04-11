/******************************************************************************/
/*!
\title		Captain Stealth
\file		ScriptComponent.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		ScriptComponent component class.
			An extension (and abstraction) of the component class.
			Is identical to the component class except that it is
			only to be used for gameplay logic and behavior.

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/

#pragma once
#include "ComponentCRTP.h"

namespace StarBangBang
{
	class Script : public Component<Script>
	{
	public:
		/*!*************************************************************************
		 * \brief 
		 * Component Constructor.
		 * Attaches the component to a game object.
		 * \param gameObject
		 * GameObject to attach to.
		***************************************************************************/
		inline Script(GameObject* gameObject) : Component(gameObject) {}

		/*!*************************************************************************
		 * \brief 
		 * Sets the status of the script.
		 * \param status
		 * True for active, false otherwise
		***************************************************************************/
		inline void SetActive(bool status) { active = status; }

		/*!*************************************************************************
		 * \brief 
		 * Start function. Called once at the start of the scene.
		***************************************************************************/
		virtual void Start() {};

		/*!*************************************************************************
		 * \brief 
		 * Update function. Called once per frame.
		***************************************************************************/
		virtual void Update() {};

		/*!*************************************************************************
		 * \brief
		 * Draw function. Called once per frame.
		***************************************************************************/
		virtual void Draw() {};

	private:
		friend class ScriptManager;
	};
}