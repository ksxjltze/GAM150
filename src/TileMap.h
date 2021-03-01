#pragma once
#include <map>
#include "ObjectManager.h"

namespace StarBangBang
{
	struct Tile;
	class TileMap
	{
	public:
		void Load(std::string path, ObjectManager& objMgr, GraphicsManager& gfxMgr);
	private:
		std::map<std::pair<int, int>, Tile> map;
	};
}