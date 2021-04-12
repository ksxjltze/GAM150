/******************************************************************************/
/*!
\title		Captain Stealth
\file		Click.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Click script.
			Invokes the set callback when the game object is clicked.

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/

#pragma once
#include "ScriptComponent.h"
#include "Utils.h"
#include "SoundEvent.h"

namespace StarBangBang
{
	template <typename ClassType>
	class Click : public Script
	{
	public:
		Click(GameObject* obj, bool overlay = false) : Script(obj), isOverlay{ overlay } {}
		Click(GameObject* obj, void (*fptr)(void)) : Script(obj), callback{ fptr } {}

		void Start() {  }
		void Update()
		{
			if (!gameObject->active)
				return;

			Transform& transform = gameObject->transform;
			if (PointRectTest(GetMouseWorldPos(!isOverlay), transform.position, transform.scale.x * GRAPHICS::MESH_WIDTH, transform.scale.y * GRAPHICS::MESH_HEIGHT))
			{
				if (AEInputCheckTriggered(AEVK_LBUTTON))
				{
					clicked = true;
				}
				else if (clicked && AEInputCheckReleased(AEVK_LBUTTON))
				{
					onClick();
					clicked = false;
				}
			}
			else if (clicked)
				clicked = false;
			
		}

		void setCallback(void (*fptr)(void)) { callback = fptr; }
		void setCallback(ClassType& inst, void (ClassType::* fptr)(void)) { callbackList.push_back({ inst, fptr }); }

		virtual void onClick()
		{
			SoundEvent(SFX::BUTTON_CLICK).SendEvent();

			if (callback)
				callback();

			for (auto cb : callbackList)
			{
				(cb.first.*(cb.second))();
			}
		}

	private:
		bool clicked{ false };
		bool isOverlay{ false };
		void (*callback)(void) { nullptr };
		std::vector<std::pair<ClassType&, void (ClassType::*)(void)>> callbackList;
	};
}