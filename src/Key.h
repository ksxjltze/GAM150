/******************************************************************************/
/*!
\title		Captain Stealth
\file		Key.h
\author 	Sim Chin Hin
\par    	email: s.chinhin\@digipen.edu
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
		Key(GameObject* obj, Door* door);

		bool isCollected();
		void Pickup();
		void onNotify(Event e);

		void Start();
		void Update();
	private:
		bool flip{ false };
		float scale;
		bool collected;
		Door* door;
	};
}