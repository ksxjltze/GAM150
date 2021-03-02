#pragma once
#include <map>
#include "ObjectManager.h"
#include "TileSet.h"

namespace StarBangBang
{
	struct Tile
	{
		ImageComponent* spriteObject;
	};

	class TileMap
	{
	public:
		TileMap();
		void Load(std::string path, ObjectManager& objMgr, GraphicsManager& gfxMgr);
		float GetTileScale();
		int GetMapWidth();
		int GetMapHeight();
	private:
		float scale;
		int mapWidth, mapHeight;

		TileSet tileSet;
		std::map<std::pair<int, int>, Tile> map;
	};
}