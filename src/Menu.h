/******************************************************************************/
/*!
\title		Captain Stealth
\file		Menu.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Menu class.
			Displays a menu overlay.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "ScriptComponent.h"
#include "GraphicsManager.h"

namespace StarBangBang
{
	class Menu : public Script
	{
	public:
		Menu(GameObject* gameObject, GraphicsManager& gfx);
		virtual void Init() = 0;
		virtual void Toggle() = 0;
		void Start();
		void Draw();
		void ForceUpdate();
		void SetStatus(bool);
		bool GetStatus() { return status; }
	protected:
		std::vector<GameObject*> buttonList;
		GraphicsManager& gfxMgr;
	private:
		bool status{ false };
	};
}