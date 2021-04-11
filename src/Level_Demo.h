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
		Level_Demo(int id, GameStateManager& manager);
		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();
	private:
		direction dir;
		current_char character;
		void DisplayExitConfirmation();
		void Exit();
		void DisplayPauseMenu();
		void TogglePause();
		void ToggleSettings();
		bool paused{ false };

		void SpawnDoors();
		void InitPause();
		void CreateDistraction(unsigned int roomNum, int tileX, int tileY, const Sprite& sprite);
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