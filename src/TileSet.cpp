#include "TileSet.h"
#include "constants.h"

namespace StarBangBang
{
	//TEST
	void TileSet::Load(GraphicsManager& gfxMgr)
	{
		Sprite grassSprite = gfxMgr.CreateSprite(RESOURCES::PROTOTYPE_SPRITE_GRASS_PATH);
		Sprite stoneSprite = gfxMgr.CreateSprite(RESOURCES::PROTOTYPE_SPRITE_STONE_PATH);

		set.insert({ TileType::GRASS, { grassSprite, TileType::GRASS } });
		set.insert({ TileType::STONE, { stoneSprite, TileType::STONE } });
	}

	//Load from path
	void StarBangBang::TileSet::Load(const std::string& path)
	{
		UNREFERENCED_PARAMETER(path);
	}

	//Load from directory
	void StarBangBang::TileSet::Load(const std::string&& dirPath)
	{
		UNREFERENCED_PARAMETER(dirPath);
	}

	const TileSprite& TileSet::GetTileSprite(TileType t)
	{
		return set.at(t);
	}

	TileType& operator++(TileType& tileType)
	{
		TileType type = TileType(static_cast<int>(tileType) + 1);
		if (type > TileType::END)
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
