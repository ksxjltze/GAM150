/******************************************************************************/
/*!
\title		Captain Stealth
\file		Door.h
\author 	Sim Chin Hin
\par    	email: s.chinhin\@digipen.edu
\date   	April 09, 2021
\brief		Door script.
			Doors block player progress and can only be opened once
			all linked keys have been collected.

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/

#pragma once
#include "ScriptComponent.h"
#include "Key.h"
#include <set>
#include <initializer_list>

namespace StarBangBang
{
	class Door : public Script
	{
	public:
		/*!*************************************************************************
		 * \brief 
		 * Script constructor.
		 * Attaches the script to a game object.
		 * \param obj
		 * GameObject to attach to.
		***************************************************************************/
		Door(GameObject* obj);

		/*!*************************************************************************
		 * \brief 
		 * Adds a key to the door.
		 * \param k
		 * Key to add.
		***************************************************************************/
		void AddKey(Key* k);

		/*!*************************************************************************
		 * \brief 
		 * Start function. Called once at the start of the scene.
		 * \return
		 * void
		***************************************************************************/
		void Start();

		/*!*************************************************************************
		 * \brief 
		 * Update function. Called once every frame.
		 * \return
		 * void
		***************************************************************************/
		void Update();

		/*!*************************************************************************
		 * \brief 
		 * Links this door objects to other doors (Sets this as parent).
		 * \param doorList
		 * Initializer list of door objects to link.
		***************************************************************************/
		void Link(std::initializer_list<Door*> doorList);
	private:
		bool open{ false };
		Door* parent;
		std::set<Key*> keys;

		/*!*************************************************************************
		 * \brief 
		 * Debug Function.
		 * Disables the doors.
		 * \return void
		***************************************************************************/
		void Debug_Disable();
	};
}