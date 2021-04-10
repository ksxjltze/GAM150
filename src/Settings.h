/******************************************************************************/
/*!
\title		Captain Stealth
\file		Settings.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat@digipen.edu
\date   	April 09, 2021
\brief		Settings Menu.
			Displays a settings menu (Overlay)
			Has buttons for muting sound and toggling fullscreen mode.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "ScriptComponent.h"
#include "GraphicsManager.h"
#include "Menu.h"

namespace StarBangBang
{
	class SettingsMenu : public Menu
	{
	public:
		SettingsMenu(GameObject* gameObject, GraphicsManager& gfx);
		void Init();
		void Toggle();
	private:
		void Back();
		void Mute();
		void Fullscreen();

		GameObject* muteBtn{ nullptr };
		GameObject* fullscreenBtn{ nullptr };
		GameObject* backBtn{ nullptr };
	};
}