/******************************************************************************/
/*!
\title		Captain Stealth
\file		Key.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Key script.
			Opens a linked door when enough keys have been collected.
			Keys are collected on collision with the client character.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "ScriptComponent.h"
#include "Listener.h"

namespace StarBangBang
{
	class Door;
	class Key : public Script, public Listener
	{
	public:
		/*!*************************************************************************
		 * \brief 
		 * Script Constructor.
		 * Attaches the script to a game object
		 * \param obj
		 * GameObject to attach to.
		 * \param door
		 * Door to link to.
		***************************************************************************/
		Key(GameObject* obj, Door* door);

		/*!*************************************************************************
		 * \brief 
		 * Accessor.
		 * \return 
		 * True if the key is collected, false otherwise.
		***************************************************************************/
		bool isCollected();

		/*!*************************************************************************
		 * \brief 
		 * Sends a key pickup event.
		 * Invoked when the correct collision event is received.
		 * \return void
		***************************************************************************/
		void Pickup();

		/*!*************************************************************************
		 * \brief 
		 * Event callback.
		 * Listens for COLLISION events that involve the 
		 * client character and the current object.
		 * \param e
		 * Event data
		 * \return
		 * void
		***************************************************************************/
		void onNotify(Event e);

		/*!*************************************************************************
		 * \brief 
		 * Start function. Called once at the start of the scene.
		***************************************************************************/
		void Start();

		/*!*************************************************************************
		 * \brief 
		 * Update function. Called once per frame.
		***************************************************************************/
		void Update();
	private:
		bool flip{ false };
		float scale;
		bool collected;
		Door* door;
	};
}