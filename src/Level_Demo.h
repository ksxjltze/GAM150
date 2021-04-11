/******************************************************************************/
/*!
\title		Captain Stealth
\file		Level_Demo.h
\author 	Lee Jia Keat
\contributions
			- Created the file, and set up the Scene.
			  Pause menu, Player movement, Switching mechanic.
\author2	Rayner Liew
\author3	Ho Yi Guan
\author4	Sim Chin Hin

\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Main game scene for Captain Stealth.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "State.h"
#include "ObjectManager.h"
#include "GraphicsManager.h"
#include "MemoryManager.h"
#include "GameStateManager.h"
#include "TileMap.h"
#include "constants.h"

namespace StarBangBang
{
	class Level_Demo : public Scene
	{
	public:
		/*!*************************************************************************
		 * \brief 
		 * Scene constructor.
		 * \param id
		 * Scene id.
		 * \param manager
		 * Reference to the game state manager.
		***************************************************************************/
		Level_Demo(int id, GameStateManager& manager);

		/*!*************************************************************************
		 * \brief 
		 * Loads all the sprites required to draw the game objects.
		 * \return
		 * void
		***************************************************************************/
		void Load();

		/*!*************************************************************************
		 * \brief
		 * Initializes and creates game objects and the tile map.
		 * \return
		 * void
		***************************************************************************/
		void Init();

		/*!*************************************************************************
		 * \brief
		 * Updates the game objects.
		 * \return
		 * void
		***************************************************************************/
		void Update();

		/*!*************************************************************************
		 * \brief
		 * Draws the game objects.
		 * \return
		 * void
		***************************************************************************/
		void Draw();

		/*!*************************************************************************
		 * \brief
		 * Frees allocated memory for game objects and components.
		 * \return
		 * void
		***************************************************************************/
		void Free();

		/*!*************************************************************************
		 * \brief
		 * Unloads sprites.
		 * \return
		 * void
		***************************************************************************/
		void Unload();
	private:
		direction dir;
		current_char character;

		/*!*************************************************************************
		 * \brief 
		 * Displays the exit confirmation menu.
		 * \return
		 * void
		***************************************************************************/
		void DisplayExitConfirmation();

		/*!*************************************************************************
		 * \brief
		 * Exits the scene (callback).
		 * \return
		 * void
		***************************************************************************/
		void Exit();

		/*!*************************************************************************
		 * \brief 
		 * Displays the pause menu.
		 * \return
		 * void
		***************************************************************************/
		void DisplayPauseMenu();

		/*!*************************************************************************
		 * \brief 
		 * Toggles pause state.
		 * \return
		 * void
		***************************************************************************/
		void TogglePause();

		/*!*************************************************************************
		 * \brief 
		 * Toggles the settings menu.
		 * \return
		 * void
		***************************************************************************/
		void ToggleSettings();
		bool paused{ false };

		/*!*************************************************************************
		 * \brief 
		 * Spawns the door objects.
		 * \return
		 * void
		***************************************************************************/
		void SpawnDoors();

		/*!*************************************************************************
		 * \brief 
		 * Initializes the pause menu.
		***************************************************************************/
		void InitPause();

		/*!*************************************************************************
		 * \brief 
		 * Creates a distraction object.
		 * \param roomNum
		 * Room to assign it to.
		 * \param tileX
		 * X position on the tilemap.
		 * \param tileY
		 * Y position on the tilemap.
		 * \param sprite
		 * Sprite of the distraction object.
		***************************************************************************/
		void CreateDistraction(unsigned int roomNum, int tileX, int tileY, const Sprite& sprite);

		/*!*************************************************************************
		 * \brief 
		 * Creates a vent object.
		 * \param tileX
		 * X position on the tilemap.
		 * \param tileY
		 * Y position on the tilemap.
		***************************************************************************/
		void CreateVent(int tileX, int tileY);

		//player stuffs
		Sprite playerImage;

		Sprite playerImageL1;
		Sprite playerImageL2;
		Sprite playerImageL3;

		Sprite playerImageR1;
		Sprite playerImageR2;
		Sprite playerImageR3;

		//player 2 stuffs
		Sprite player2Image;

		Sprite playerImage2L1;
		Sprite playerImage2L2;
		Sprite playerImage2L3;

		Sprite playerImage2R1;
		Sprite playerImage2R2;
		Sprite playerImage2R3;

		//Indicator
		Sprite indicator;

		Sprite guardImage;
		Sprite securityCamImage;
		Sprite vendingMachineSprite;

		GameObject* movementController;
		GameObject* player;
		GameObject* player2;
		GameObject* guardManager;
		GameObject* indicatorObj;

		//Vents
		Sprite ventOpenSprite;
		Sprite ventCloseSprite;


		TileMap tilemap;
	};
}