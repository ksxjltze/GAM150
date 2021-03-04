#pragma once
#include <map>
#include "ObjectManager.h"
#include "TileSet.h"

namespace StarBangBang
{
	struct Tile
	{
		ImageComponent* spriteObject;
		TileType type;
	};

	class TileMap
	{
	public:
		TileMap(ObjectManager&, GraphicsManager&);

		void Init();

		void Generate(int width, int height, float tileSize);
		bool ValidateFile(std::ifstream& is, std::string& widthStr, std::string& heightStr, std::string& sizeStr);
		void Save(std::string path);
		bool Load(std::string path);

		float GetTileScale();


		/// <summary>
		/// Calculates the offset for the translation of the tile map's origin.
		/// Assumes calculations from centre of tile map.
		/// </summary>
		/// <param name="pos">Position to offset to</param>
		/// <returns>Offset Vector</returns>
		AEVec2 GetCentreOffset(AEVec2 pos = { 0, 0 });
		void SetPosition(AEVec2 pos);

		int GetMapWidth();
		int GetMapHeight();

		void Insert(int x, int y, TileType type);
		void Erase(int x, int y);

		Tile CreateNewTile(AEVec2 pos, TileSprite tileSprite);

	private:
		GameObject* base{ nullptr };
		float scale;
		int mapWidth, mapHeight;

		ObjectManager& objMgr;
		GraphicsManager& gfxMgr;

		TileSet tileSet;
		std::map<std::pair<int, int>, Tile> map;
	};
}