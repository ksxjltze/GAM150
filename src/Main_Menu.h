/******************************************************************************/
/*!
\title		Captain Stealth
\file		Main_Menu.h
\author 	Sim Chin Hin
\author2	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Credits scene.

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

namespace StarBangBang
{
	class Main_Menu: public Scene
	{
	public:
		Main_Menu(int id, GameStateManager& manager);
		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();

		void LoadEditor();
		void LoadTutorial();
		void LoadLevel();
		void Credits();
		void ExitGame();

		void Settings();

	private:
		void DisplayConfirmationMenu();
		void HideMenu();

		TileMap tilemap;
		Sprite logo;
		Sprite playbutton1;
		Sprite settingsbutton1;
		Sprite creditsbutton1;
		Sprite exitbutton1;
		Sprite tutorialButton1;

		Sprite playbutton2;
		Sprite settingsbutton2;
		Sprite creditsbutton2;
		Sprite exitbutton2;

		GameObject* logo_obj;
		GameObject* playbutton_obj;
		GameObject* settingsbutton_obj;
		GameObject* creditsbutton_obj;
		GameObject* exitbutton_obj;
		GameObject* tutorialbutton_obj;
		GameObject* settingsObj{ nullptr };
		GameObject* confirmationObj{ nullptr };
		GameObject* editorBtn{ nullptr };

		//GameObject* editorBtn{ nullptr };

		bool windowOpen{ false };
		std::queue<GameObject*> windowQueue;
		bool tf;
		bool frameSkip{ false };
	};
}