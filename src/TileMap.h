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
	private:
		float tileWidth, tileHeight;
		float mapWidth, mapHeight;

		TileSet tileSet;
		std::map<std::pair<int, int>, Tile> map;
	};
}