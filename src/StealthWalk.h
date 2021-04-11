/*!*********************************************************************
\title	  Captain Stealth
\file     StealthWalk.h
\author   Sim Chin Hin
\par      DP email: s.chinhin\@digipen.edu
\date     11/04/2021

\brief
		  This file contains script class for stealthwalk

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
***********************************************************************/
#pragma once
#include "ScriptComponent.h"
#include "ImageComponent.h"
#include "UIComponent.h"
#include "Text.h"

namespace StarBangBang
{
	
	class StealthWalk : public Script
	{
	public:
		/*!*********************************************************************
		\brief
			Non-default constructor

		\param gameObject
			The game object that will use this script
		***********************************************************************/
		StealthWalk(GameObject* gameObject);
		/*!*********************************************************************
		\brief
			Initialise stealth walk
		***********************************************************************/
		void Start();
		/*!*********************************************************************
		\brief
			Updates stealth walk status
		***********************************************************************/
		void Update();
		/*!*********************************************************************
		\brief
			Get invisible status
		\return
			bool invisible status
		***********************************************************************/
		bool IsInvisible() { return invisible; }
		/*!*********************************************************************
		\brief
			Gets timer left on stealthwalk
		\return
			float timer
		***********************************************************************/
		float GetTimer() { return timer; }
		/*!*********************************************************************
		\brief
			Gets cooldown timer
		\return
			float cooldown timer
		***********************************************************************/
		float GetCooldown() { return cooldown; }
	private:
		ImageComponent* image;
		UIComponent* icon_image;
		Text* cd_txt;
		float timer;
		float cooldown;
		bool invisible = false;
		
	};
}