/******************************************************************************/
/*!
\title		Captain Stealth
\file		TileSet.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat@digipen.edu
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

#include "TileSet.h"
#include "constants.h"

namespace StarBangBang
{
	static std::map<TileType, const std::string> tileTypeNames;

	/**
	 * Maps a tile type to a name and inserts it into the map object.
	 * 
	 * \param type Type of tile.
	 * \param name Name of the tile type.
	 */
	void RegisterTileType(TileType type, const std::string&& name)
	{
		tileTypeNames.insert({ type, name });
	}

	void TileSet::Load(GraphicsManager& gfxMgr)
	{
		LoadTileSprite(gfxMgr,	TileType::GRASS,			RESOURCES::PROTOTYPE_SPRITE_GRASS_PATH);
		LoadTileSprite(gfxMgr,	TileType::STONE,			RESOURCES::PROTOTYPE_SPRITE_STONE_PATH);
		LoadTileSprite(gfxMgr,	TileType::BRICK_BLACK,		RESOURCES::BLACKBRICK_PATH);
		LoadTileSprite(gfxMgr,	TileType::FLOOR_PRISON,		RESOURCES::PRISONFLOOR_PATH);
		LoadTileSprite(gfxMgr,	TileType::BRICK_RED,		RESOURCES::REDBRICK_PATH);
		LoadTileSprite(gfxMgr,	TileType::FLOOR_PRISON2,	RESOURCES::PRISONFLOOR_PATH);

		RegisterTileType(TileType::GRASS,			"GRASS");
		RegisterTileType(TileType::STONE,			"STONE");
		RegisterTileType(TileType::FLOOR_PRISON,	"FLOOR_PRISON");
		RegisterTileType(TileType::BRICK_BLACK,		"BRICK_BLACK");
		RegisterTileType(TileType::FLOOR_PRISON2,	"FLOOR_PRISON2");
		RegisterTileType(TileType::BRICK_RED,		"BRICK_RED");
		
	}

	void TileSet::LoadTileSprite(GraphicsManager& gfxMgr, TileType type, const std::string& path)
	{
		Sprite sprite = gfxMgr.CreateSprite(path);
		set.insert({ type, { sprite, type } });
	}

	void TileSet::Clear()
	{
		set.clear();
	}

	const std::string& TileSet::GetTileTypeName(TileType type)
	{
		return tileTypeNames.at(type);
	}

	const TileSprite& TileSet::GetTileSprite(TileType t)
	{
		return set.at(t);
	}

	/**
	 * TileType Pre-increment operator.
	 * Mainly used in the level editor to switch between tile types.
	 * 
	 * \param tileType 
	 * Previous Tile Type.
	 * \return 
	 * Next Tile Type.
	 */
	TileType& operator++(TileType& tileType)
	{
		TileType type = TileType(static_cast<int>(tileType) + 1);
		if (type >= TileType::END)
		{
			type = TileType(static_cast<int>(TileType::NONE) + 1);
		}

		tileType = type;
		return tileType;
	}

	/**
	 * TileType Post-increment operator.
	 * Mainly used in the level editor to switch between tile types.
	 *
	 * \param tileType
	 * Previous Tile Type.
	 * \return
	 * Next Tile Type.
	 */
	TileType operator++(TileType& tileType, int)
	{
		TileType temp = tileType;
		++tileType;
		return temp;
	}
}
