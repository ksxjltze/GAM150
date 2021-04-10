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

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
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
		void Load(GraphicsManager&);
		void LoadTileSprite(GraphicsManager&, TileType type, const std::string& path);
		void Clear();
		const std::string& GetTileTypeName(TileType type);
		const TileSprite& GetTileSprite(TileType);
	private:
		std::map<TileType, TileSprite> set;
	};

	TileType& operator++(TileType& tileType);
	TileType operator++(TileType& tileType, int);
}