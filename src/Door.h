/******************************************************************************/
/*!
\title		Captain Stealth
\file		Door.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Door script.
			Doors block player progress and can only be opened once
			all linked keys have been collected.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
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
		Door(GameObject* obj);
		void AddKey(Key* k);
		void Start();
		void Update();
		void Link(std::initializer_list<Door*> doorList);
	private:
		bool open{ false };
		Door* parent;
		std::set<Key*> keys;
		void Debug_Disable();
	};
}