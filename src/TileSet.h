/******************************************************************************/
/*!
\title		Captain Stealth
\file		TileSet.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		TileSet class:
			Is used to determine the type of each Tile and loading
			their respective sprites.

			TileType enum:
			Represents the types of available tiles.
			Used to correctly load the correct tiles from the level data file.

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/

#pragma once
#include "GraphicsManager.h"
#include <map>

namespace StarBangBang
{
	enum class TileType
	{
		NONE = 0,
		GRASS,
		STONE,
		BRICK_BLACK,
		FLOOR_PRISON,
		FLOOR_PRISON2,
		BRICK_RED,
		END,
	};

	struct TileSprite
	{
		Sprite sprite;
		TileType type;
	};

	class TileSet
	{
	public:
		/*!*************************************************************************
		 * \brief 
		 * Loads the sprites for each tile type in the tile set.
		 * \param gfxMgr
		 * Reference to the graphics manager.
		***************************************************************************/
		void Load(GraphicsManager& gfxMgr);

		/*!*************************************************************************
		 * \brief 
		 * Loads the sprite for one tile type.
		 * \param gfxMgr
		 * Reference to the graphics manager.
		 * \param type
		 * Type of the tile.
		 * \param path
		 * Path to the texture file.
		***************************************************************************/
		void LoadTileSprite(GraphicsManager& gfxMgr, TileType type, const std::string& path);

		/*!*************************************************************************
		 * \brief
		 * Clears the tile set.
		 * \return
		 * void
		***************************************************************************/
		void Clear();

		/*!*************************************************************************
		 * \brief 
		 * Gets the name of a tile type.
		 * \param type
		 * Tile type.
		 * \return 
		 * Name of the tile type.
		***************************************************************************/
		const std::string& GetTileTypeName(TileType type);

		/*!*************************************************************************
		 * \brief 
		 * Gets the sprite of a tile type.
		 * \param type
		 * Tile type.
		 * \return 
		 * Reference to the TileSprite object for the specified type.
		***************************************************************************/
		const TileSprite& GetTileSprite(TileType type);
	private:
		std::map<TileType, TileSprite> set;
	};

	/*!*************************************************************************
	 * TileType Pre-increment operator.
	 * Mainly used in the level editor to switch between tile types.
	 * \param tileType
	 * Previous Tile Type.
	 * \return
	 * Next Tile Type.
	 ***************************************************************************/
	TileType& operator++(TileType& tileType);

	/*!*************************************************************************
	 * TileType Post-increment operator.
	 * Mainly used in the level editor to switch between tile types.
	 *
	 * \param tileType
	 * Previous Tile Type.
	 * \return
	 * Next Tile Type.
	 ***************************************************************************/
	TileType operator++(TileType& tileType, int);
}