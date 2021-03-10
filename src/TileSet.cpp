#include "TileSet.h"
#include "constants.h"

namespace StarBangBang
{
	//TEST
	void TileSet::Load(GraphicsManager& gfxMgr)
	{
		CreateTileSprite(gfxMgr,	TileType::GRASS,			RESOURCES::PROTOTYPE_SPRITE_GRASS_PATH);
		CreateTileSprite(gfxMgr,	TileType::STONE,			RESOURCES::PROTOTYPE_SPRITE_STONE_PATH);
		CreateTileSprite(gfxMgr,	TileType::BRICK_BLACK,		RESOURCES::REDBRICK_PATH);
		CreateTileSprite(gfxMgr,	TileType::BRICK_RED,		RESOURCES::BLACKBRICK_PATH);
		CreateTileSprite(gfxMgr,	TileType::FLOOR_OFFICE,		RESOURCES::OFFICEFLOOR_PATH);
		CreateTileSprite(gfxMgr,	TileType::FLOOR_PRISON,		RESOURCES::PRISONFLOOR_PATH);
	}

	void TileSet::CreateTileSprite(GraphicsManager& gfxMgr, TileType type, const std::string& path)
	{
		Sprite sprite = gfxMgr.CreateSprite(path);
		set.insert({ type, { sprite, type } });
	}

	const TileSprite& TileSet::GetTileSprite(TileType t)
	{
		return set.at(t);
	}

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

	TileType operator++(TileType& tileType, int)
	{
		TileType temp = tileType;
		++tileType;
		return temp;
	}
}
