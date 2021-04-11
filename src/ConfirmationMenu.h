/******************************************************************************/
/*!
\title		Captain Stealth
\file		ConfirmationMenu.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Confirmation Menu.
			Displays a confirmation menu for destructive actions.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "Settings.h"

namespace StarBangBang
{
	class GameStateManager;
	class ConfirmationMenu : public Menu
	{
	public:
		/*!*************************************************************************
		 * \brief 
		 * Menu (Script) constructor.
		 * \param gameObject
		 * GameObject to attach to.
		 * \param gfx
		 * Reference to the graphics manager.
		 * \param gsm
		 * Reference to the game state manager.
		 * \param type
		 * Type of confirmation.
		***************************************************************************/
		ConfirmationMenu(GameObject* gameObject, GraphicsManager& gfx, GameStateManager& gsm, int type = 0);

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

		/*!*************************************************************************
		 * \brief 
		 * Sets the text to display.
		 * \param s
		 * String to display.
		***************************************************************************/
		void SetText(const std::string& s);
	private:
		/*!*************************************************************************
		 * \brief 
		 * Confirm callback.
		 * \return 
		 * void
		***************************************************************************/
		void Confirm();

		/*!*************************************************************************
		 * \brief 
		 * Back callback.
		 * \return
		 * void
		***************************************************************************/
		void Back();

		GameStateManager& gsm;
		GameObject* confirmBtn{ nullptr };
		GameObject* textObject{ nullptr };
		GameObject* backBtn{ nullptr };
		int type{ 0 };
	};
}