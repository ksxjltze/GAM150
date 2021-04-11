/******************************************************************************/
/*!
\title		Captain Stealth
\file		Scene_GameOver.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		GameOver scene.
			Displayed when the player loses the game.

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/

#pragma once
#include "State.h"

namespace StarBangBang
{
	class Scene_GameOver : public Scene
	{
	public:
		/*!*************************************************************************
		 * \brief 
		 * Scene constructor.
		 * \param id
		 * Scene id
		 * \param gsm
		 * Reference to the game state manager.
		***************************************************************************/
		Scene_GameOver(int id, GameStateManager& gsm);

		/*!*************************************************************************
		 * \brief 
		 * Loads the button sprites.
		 * \return
		 * void
		***************************************************************************/
		void Load();

		/*!*************************************************************************
		 * \brief
		 * Initializes the buttons and text.
		 * \return
		 * void
		***************************************************************************/
		void Init();

		/*!*************************************************************************
		 * \brief
		 * Updates components and game objects.
		 * \return
		 * void
		***************************************************************************/
		void Update();

		/*!*************************************************************************
		 * \brief
		 * Draws the buttons and text.
		 * \return
		 * void
		***************************************************************************/
		void Draw();

		/*!*************************************************************************
		 * \brief
		 * Frees the game objects and components.
		 * \return
		 * void
		***************************************************************************/
		void Free();

		/*!*************************************************************************
		 * \brief
		 * Unloads the button sprites.
		 * \return
		 * void
		***************************************************************************/
		void Unload();
	private:

		/*!*************************************************************************
		 * \brief 
		 * Quits the game (Return to title screen).
		 * \return
		 * void
		***************************************************************************/
		void Quit();

		/*!*************************************************************************
		 * \brief 
		 * Restarts the game.
		 * \return void
		***************************************************************************/
		void Restart();
		GameObject* quitBtn;
		GameObject* restartBtn;
	};

}