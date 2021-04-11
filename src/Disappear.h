/*!*********************************************************************
\title	  Captain Stealth
\file     Disappear.h
\author   Sim Chin Hin
\par      DP email: s.chinhin\@digipen.edu
\date     11/04/2021

\brief
		  This file contains the script class players 
		  disappearing into the vents

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
***********************************************************************/
#pragma once
#include "ScriptComponent.h"
#include "Listener.h"
#include "Sprite.h"

namespace StarBangBang
{
	class Disappear : public Script, public Listener
	{
	public:
		/*!*********************************************************************
		\brief
			Non-default constructor

		\param gameObject
			The game object that will use this script
		\param ventOpen_
			open vent sprite
		\param ventClose_
			closed vent sprite
		***********************************************************************/
		Disappear(GameObject* gameObject, Sprite& ventOpen_, Sprite& ventClose_);
		/*!*********************************************************************
		\brief
			Initialise vent's starting state
		***********************************************************************/
		void Start();
		/*!*********************************************************************
		\brief
			Update vent's current state
		***********************************************************************/
		void Update();
		/*!*********************************************************************
		\brief
			Change vent's sprite and state when notified
		***********************************************************************/
		void onNotify(Event e);

	private:
		bool hidden, ventClosed;
		Sprite& ventOpen;
		Sprite& ventClose;
	};
}
