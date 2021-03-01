#pragma once
#include <map>
#include "ObjectManager.h"

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
		std::map<std::pair<int, int>, Tile> map;
	};
}