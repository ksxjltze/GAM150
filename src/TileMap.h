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
		TileMap(ObjectManager&, GraphicsManager&);
		void Generate(int width, int height, float tileSize);
		void Load(std::string path);
		float GetTileScale();
		int GetMapWidth();
		int GetMapHeight();
	private:
		float scale;
		int mapWidth, mapHeight;

		ObjectManager& objMgr;
		GraphicsManager& gfxMgr;

		TileSet tileSet;
		std::map<std::pair<int, int>, Tile> map;
	};
}