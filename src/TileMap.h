/******************************************************************************/
/*!
\title		Captain Stealth
\file		TileMap.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		TileMap class.
			Responsible for loading tiles from the level data file.
			Or generating new tile maps.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "ObjectManager.h"
#include "GraphicsManager.h"
#include "TileSet.h"
#include "Grid.h"
#include <map>

namespace StarBangBang
{
	struct Tile
	{
		ImageComponent* spriteObject;
		TileType type;
		bool collidable;
	};

	class TileMap
	{
	public:
		/*!*************************************************************************
		 * \brief 
		 * TileMap Constructor.
		 * \param objM
		 * Reference to the scene's object manager.
		 * \param gfxM
		 * Reference to the scene's graphics manager.
		***************************************************************************/
		TileMap(ObjectManager& objM, GraphicsManager& gfxM);

		/*!*************************************************************************
		 * \brief 
		 * Init function.
		 * Loads the tile set and creates the game object for the tile map.
		 * \return
		 * void
		***************************************************************************/
		void Init();

		/*!*************************************************************************
		 * \brief 
		 * Generates a new tile map.
		 * \param width
		 * Width of the tile map.
		 * \param height
		 * Height of the tile map.
		 * \param tileSize
		 * Size of each tile.
		 * \param type
		 * Tile Type to fill the new map.
		 * \return
		 * void
		***************************************************************************/
		void Generate(int width, int height, float tileSize, TileType type = TileType::STONE);

		/*!*************************************************************************
		 * \brief 
		 * Validates if the file is valid for loading.
		 * \param is
		 * Input file stream Reference.
		 * \param widthStr
		 * Width Tag string to check against.
		 * \param heightStr
		 * Height Tag string to check against.
		 * \param sizeStr
		 * Size Tag string to check against.
		 * \return
		 * True if valid, false otherwise
		***************************************************************************/
		bool ValidateFile(std::ifstream& is, std::string& widthStr, std::string& heightStr, std::string& sizeStr);

		/*!*************************************************************************
		 * \brief 
		 * Saves the tile map to the specified path.
		 * \param path
		 * File path to save to.
		 * \return
		 * void
		***************************************************************************/
		void Save(std::string path);

		/*!*************************************************************************
		 * \brief
		 * Loads the tile map from the specified path.
		 * \param path
		 * File path to load from.
		***************************************************************************/
		bool Load(std::string path);

		/*!*************************************************************************
		 * \brief 
		 * Clears the tile map.
		 * \return
		 * void
		***************************************************************************/
		void Clear();

		/*!*************************************************************************
		 * \brief 
		 * Fills the tile map with the specified tile type.
		 * \return
		 * void
		***************************************************************************/
		void Fill(TileType type);

		/*!*************************************************************************
		 * \brief 
		 * Unloads the tile map, clearing all tiles.
		 * \return
		 * void
		***************************************************************************/
		void Unload();
		
		/*!*************************************************************************
		 * \brief 
		 * Gets the scale of each tile.
		 * \return
		 * Size of each tile.
		***************************************************************************/
		float GetTileScale();

		/*!*************************************************************************
		 * \brief 
		 * Calculates the offset for the translation of 
		 * Assumes calculations from center of tile map.
		 * \param pos
		 * Position to offset to.
		 * \return
		 * Offset Vector
		***************************************************************************/
		AEVec2 GetCentreOffset(AEVec2 pos = { 0, 0 });

		/*!*************************************************************************
		 * \brief 
		 * Sets the position of the tile map.
		 * \param pos
		 * Position to set.
		 * \return void
		***************************************************************************/
		void SetPosition(AEVec2 pos);

		/*!*************************************************************************
		 * \brief 
		 * Gets the position of the cell at the specified index/coordinates of the map
		 * \param x
		 * X coordinate.
		 * \param y
		 * Y coordinate.
		 * \return
		 * The world position of the cell at the index.
		***************************************************************************/
		AEVec2 GetPositionAtIndex(int x, int y);

		/*!*************************************************************************
		 * \brief
		 * Gets the tile at the specified index/coordinates of the map.
		 * \param x
		 * X coordinate.
		 * \param y
		 * Y coordinate.
		 * \return
		 * Reference to the tile object at the index
		***************************************************************************/
		Tile& At(int x, int y);

		/*!*************************************************************************
		 * \brief 
		 * Gets the width of the map.
		 * \return
		 * Width of the map.
		***************************************************************************/
		int GetMapWidth();

		/*!*************************************************************************
		 * \brief
		 * Gets the height of the map.
		 * \return
		 * Height of the map.
		***************************************************************************/
		int GetMapHeight();

		/*!*************************************************************************
		 * \brief 
		 * Sets the cells on the grid that corresponds to the tile map.
		 * Required for path finding to work correctly.
		 * \param grid
		 * Grid to set.
		 * \return
		 * void
		***************************************************************************/
		void SetGrid(Grid& grid);

		/*!*************************************************************************
		 * \brief 
		 * Inserts a tile at the specified coordinates.
		 * \param x
		 * X coordinate.
		 * \param y
		 * Y coordinate.
		 * \param type
		 * Type of the tile to insert.
		 * \return
		 * void
		***************************************************************************/
		void Insert(int x, int y, TileType type);

		/*!*************************************************************************
		 * \brief 
		 * Replaces the tile at the specified coordinates.
		 * \param x
		 * X coordinate.
		 * \param y
		 * Y coordinate.
		 * \param type
		 * Type of the tile to insert.
		 * \return
		 * void
		***************************************************************************/
		void Replace(int x, int y, TileType type);

		/*!*************************************************************************
		 * \brief 
		 * Erases the tile at the specified coordinates.
		 * \param x
		 * X coordinate.
		 * \param y
		 * Y coordinate.
		 * \return
		 * void
		***************************************************************************/
		void Erase(int x, int y);

		/*!*************************************************************************
		 * \brief 
		 * Creates a new tile at the specified position.
		 * \param pos
		 * Position to place the tile.
		 * \param tileSprite
		 * Sprite of the tile.
		 * \param collidable
		 * True if the tile is collidable, false otherwise
		 * \return
		 * The Tile object that was created
		***************************************************************************/
		Tile CreateNewTile(AEVec2 pos, TileSprite tileSprite, bool collidable = false);

		/*!*************************************************************************
		 * \brief
		 * Replaces the tile at the specified position.
		 * \param tile
		 * Tile to replace.
		 * \param pos
		 * Position to place the tile.
		 * \param tileSprite
		 * Sprite of the tile.
		 * \return
		 * The Tile object that was created
		***************************************************************************/
		Tile ReplaceTile(Tile tile, AEVec2 pos, TileSprite tileSprite);

		/*!*************************************************************************
		 * \brief 
		 * Sets the types of tiles that are collidable.
		 * \param typeList
		 * initializer list of the types to set
		 * \return
		 * void
		***************************************************************************/
		void SetCollidableTypes(std::initializer_list<TileType> typeList);

		/*!*************************************************************************
		 * \brief 
		 * Sets whether the tile map should be visible.
		 * \param visible
		 * True if visible, false otherwise
		 * \return
		 * void
		***************************************************************************/
		void SetVisible(bool visible);

	private:
		friend class LevelEditor;
		GameObject* base;
		float scale;
		int mapWidth, mapHeight;

		ObjectManager& objMgr;
		GraphicsManager& gfxMgr;

		TileSet tileSet;
		std::vector<TileType> collidableList;
		std::map<std::pair<int, int>, Tile> map;
	};
}