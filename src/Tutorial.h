/*!*********************************************************************
\file     Tutorial.h
\author   Liew Ruiheng Rayner
\par      DP email: r.liew\@digipen.edu
\date     08/04/2021

\brief
  This file contains the Tutorial scene class
***********************************************************************/

#pragma once
#include "State.h"
#include "TileMap.h"

namespace StarBangBang
{
	class Tutorial : public Scene
	{
	public:
		/*!*********************************************************************
		\brief
			Non-default constructor

		\param id
			The id of the scene

		\param gsm
			Reference to the game statemanager
		***********************************************************************/
		Tutorial(int id, GameStateManager& gsm);

		/*!*********************************************************************
		\brief
			Loads assets for this scene
		***********************************************************************/
		void Load();

		/*!*********************************************************************
		\brief
			Initializes the game objects for this scene
		***********************************************************************/
		void Init();

		/*!*********************************************************************
		\brief
			Updates this scene
		***********************************************************************/
		void Update();

		/*!*********************************************************************
		\brief
			Draws this scene
		***********************************************************************/
		void Draw();

		/*!*********************************************************************
		\brief
			Frees this scene
		***********************************************************************/
		void Free();

		/*!*********************************************************************
		\brief
			Unloads this scene
		***********************************************************************/
		void Unload();

	private:
		/*!*********************************************************************
		\brief
			Unloads this scene
		***********************************************************************/
		void NewTextObject(AEVec2 position, const std::string& s, float scale = 1.0f);

		GameObject* cameraObject;
		GameObject* end;
		GameObject* player{ nullptr };
		GameObject* player2{ nullptr };
		void MainMenu();

		direction dir;
		current_char character;

		Sprite tutorialSprite;
		Sprite movementSprite;
		Sprite tabSprite;
		Sprite ventSprite;
		Sprite distractSprite;
		Sprite distractSprite2;
		Sprite backSprite;
		TileMap tilemap;
	};

}