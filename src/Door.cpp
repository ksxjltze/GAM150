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
	Door::Door(GameObject* obj) : Script(obj), parent{ nullptr }
	{

	}

	void Door::AddKey(Key* k)
	{
		keys.insert(k);
	}

	void Door::Start()
	{
		for (auto k : keys)
		{
			k->gameObject->active = true;
		}
		open = false;
	}

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

	void Door::Link(std::initializer_list<Door*> doorList)
	{
		for (auto door : doorList)
		{
			door->parent = this;
		}
	}

	void Door::Debug_Disable()
	{
		if (AEInputCheckTriggered(AEVK_K))
		{
			gameObject->active = false;
		}
	}
}