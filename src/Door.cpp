/******************************************************************************/
/*!
\title		Captain Stealth
\file		Door.cpp
\author 	Lee Jia Keat
\par    	email: s.chinhin\@digipen.edu
\date   	April 09, 2021
\brief		Door script.
			Doors block player progress and can only be opened once
			all linked keys have been collected.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#include "Door.h"
#include "SoundEvent.h"
#include "globals.h"

namespace StarBangBang
{
	/*!*************************************************************************
	 * \brief
	 * Script constructor.
	 * Attaches the script to a game object.
	 * \param obj
	 * GameObject to attach to.
	***************************************************************************/
	Door::Door(GameObject* obj) : Script(obj), parent{ nullptr }
	{

	}

	/*!*************************************************************************
	 * \brief
	 * Adds a key to the door.
	 * \param k
	 * Key to add.
	***************************************************************************/
	void Door::AddKey(Key* k)
	{
		keys.insert(k);
	}

	/*!*************************************************************************
	 * \brief
	 * Start function. Called once at the start of the scene.
	 * \return
	 * void
	***************************************************************************/
	void Door::Start()
	{
		for (auto k : keys)
		{
			k->gameObject->active = true;
		}
		open = false;
	}

	/*!*************************************************************************
	 * \brief
	 * Update function. Called once every frame.
	 * \return
	 * void
	***************************************************************************/
	void Door::Update()
	{
		if (IsDebug())
			Debug_Disable();

		std::set<Key*> keyList = keys;
		if (parent)
		{
			keyList = parent->keys;
		}

		for (auto k : keyList)
		{
			if (!k->isCollected())
				return;
		}

		if (!open)
		{
			gameObject->active = false;
			open = true;
			
			if (!parent)
			{
				SoundEvent doorOpenSound(SFX::DOOR_OPEN);
				doorOpenSound.SendEvent();
			}
		}

	}

	/*!*************************************************************************
	 * \brief
	 * Links this door objects to other doors (Sets this as parent).
	 * \param doorList
	 * Initializer list of door objects to link.
	***************************************************************************/
	void Door::Link(std::initializer_list<Door*> doorList)
	{
		for (auto door : doorList)
		{
			door->parent = this;
		}
	}

	/*!*************************************************************************
	 * \brief
	 * Debug Function.
	 * Disables the doors.
	 * \return void
	***************************************************************************/
	void Door::Debug_Disable()
	{
		if (AEInputCheckTriggered(AEVK_K))
		{
			gameObject->active = false;
		}
	}
}