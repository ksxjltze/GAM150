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

		void Init();
		void Generate(int width, int height, float tileSize);
		void Load(std::string path);

		float GetTileScale();

		int GetMapWidth();
		int GetMapHeight();

		void Insert(int x, int y, TileType type);
		void Erase(int x, int y);

		Tile CreateNewTile(AEVec2 pos, TileSprite tileSprite);

	private:
		float scale;
		int mapWidth, mapHeight;

		ObjectManager& objMgr;
		GraphicsManager& gfxMgr;

		TileSet tileSet;
		std::map<std::pair<int, int>, Tile> map;
	};
}