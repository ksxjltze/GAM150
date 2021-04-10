/******************************************************************************/
/*!
\title		Captain Stealth
\file		LevelEditor.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat@digipen.edu
\date   	April 09, 2021
\brief		Level Editor scene.
			Load and Save levels (tilemap).

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "State.h"
#include "GameStateManager.h"
#include "Sprite.h"
#include "Grid.h"
#include "CameraComponent.h"
#include "TileMap.h"
#include "DebugText.h"

namespace StarBangBang
{
	enum class BrushMode;

	class LevelEditor : public Scene
	{
	public:
		LevelEditor(int id, GameStateManager& manager);
		~LevelEditor();

		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();
	private:
		void InsertTile(A_Node* n);
		void RemoveTile(A_Node* n);
		void SaveLevel(const std::string& path);
		bool LoadLevel(const std::string& path);
		void CreateLevel(int width, int height, float tileSize, TileType type);
		void SetGrid();
		
		std::string filepath;
		BrushMode brushMode;

		TileMap tileMap;
		TileType selectedType;
		Grid grid;

		GameObject* camera{ nullptr };
		GameObject* debugText{ nullptr };
		GameObject* tileOutline{ nullptr };
		ImageComponent* tileImg{ nullptr };
	};
}