/******************************************************************************/
/*!
\title		Captain Stealth
\file		Settings.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Settings Menu.
			Displays a settings menu (Overlay)
			Has buttons for muting sound and toggling fullscreen mode.

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
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
		/*!*************************************************************************
		 * \brief 
		 * Menu Constructor (Script).
		 * \param gameObject
		 * GameObject to attach to.
		 * \param gfx
		 * Reference to the graphics manager.
		***************************************************************************/
		SettingsMenu(GameObject* gameObject, GraphicsManager& gfx);

		/*!*************************************************************************
		 * \brief 
		 * Initializes the menu.
		 * \return
		 * void
		***************************************************************************/
		void Init();

		/*!*************************************************************************
		 * \brief 
		 * Toggles the menu.
		 * \return
		 * void
		***************************************************************************/
		void Toggle();
	private:

		/*!*************************************************************************
		 * \brief 
		 * Back callback.
		 * \return
		 * void
		***************************************************************************/
		void Back();

		/*!*************************************************************************
		 * \brief 
		 * Mute callback.
		 * \return
		 * void
		***************************************************************************/
		void Mute();

		/*!*************************************************************************
		 * \brief 
		 * Fullscreen callback.
		 * \return void
		***************************************************************************/
		void Fullscreen();

		GameObject* muteBtn{ nullptr };
		GameObject* fullscreenBtn{ nullptr };
		GameObject* backBtn{ nullptr };
	};
}