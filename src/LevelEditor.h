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
		/*!*************************************************************************
		 * \brief 
		 * Scene Constructor.
		 * \param id
		 * Scene Id
		 * \param manager
		 * Reference to the game state manager.
		***************************************************************************/
		LevelEditor(int id, GameStateManager& manager);

		/*!*************************************************************************
		 * \brief 
		 * Destructor.
		***************************************************************************/
		~LevelEditor();
		
		/*!*************************************************************************
		 * \brief 
		 * Load.
		 * \return
		 * void
		***************************************************************************/
		void Load();

		/*!*************************************************************************
		 * \brief 
		 * Initializes  the tile map, camera, tile types, etc.
		 * \return
		 * void
		***************************************************************************/
		void Init();

		/*!*************************************************************************
		 * \brief 
		 * Updates the editor.
		 * \return
		 * void
		***************************************************************************/
		void Update();

		/*!*************************************************************************
		 * \brief 
		 * Draws.
		 * \return
		 * void
		***************************************************************************/
		void Draw();

		/*!*************************************************************************
		 * \brief 
		 * Frees the tile map.
		 * \return void
		***************************************************************************/
		void Free();

		/*!*************************************************************************
		 * \brief 
		 * Unload.
		 * \return void
		***************************************************************************/
		void Unload();
	private:

		/*!*************************************************************************
		 * \brief 
		 * Inserts a tile at the specified node.
		 * \param n
		 * Node to insert at.
		***************************************************************************/
		void InsertTile(A_Node* n);

		/*!*************************************************************************
		 * \brief 
		 * Removes the tile at the specified node.
		 * \param n
		 * Node to remove tile from.
		***************************************************************************/
		void RemoveTile(A_Node* n);

		/*!*************************************************************************
		 * \brief 
		 * Saves the tile map.
		 * \param path
		 * Path to save to.
		 * \return
		 * void
		***************************************************************************/
		void SaveLevel(const std::string& path);

		/*!*************************************************************************
		 * \brief 
		 * Loads the tile map.
		 * \param path
		 * Path to load from.
		 * \return 
		 * True if successfully loaded, false otherwise.
		***************************************************************************/
		bool LoadLevel(const std::string& path);

		/*!*************************************************************************
		 * \brief 
		 * Generates a level.
		 * \param width
		 * Width of the map.
		 * \param height
		 * Height of the map.
		 * \param tileSize
		 * Size of each tile.
		 * \param type
		 * Type to fill the map with.
		***************************************************************************/
		void CreateLevel(int width, int height, float tileSize, TileType type);

		/*!*************************************************************************
		 * \brief 
		 * Initializes and resets the editor grid.
		***************************************************************************/
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