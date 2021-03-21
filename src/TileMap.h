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
		bool collidable;
	};

	class TileMap
	{
	public:
		TileMap(ObjectManager&, GraphicsManager&);

		void Init();

		void Generate(int width, int height, float tileSize, TileType type = TileType::STONE);
		bool ValidateFile(std::ifstream& is, std::string& widthStr, std::string& heightStr, std::string& sizeStr);
		void Save(std::string path);
		bool Load(std::string path);
		void Clear();
		void Unload();

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
		void Replace(int x, int y, TileType type);
		void Erase(int x, int y);

		Tile CreateNewTile(AEVec2 pos, TileSprite tileSprite, bool collidable = false);
		Tile ReplaceTile(Tile tile, AEVec2 pos, TileSprite tileSprite);
		void SetCollidableTypes(std::initializer_list<TileType> typeList);

	private:
		GameObject* base;
		float scale;
		int mapWidth, mapHeight;

		ObjectManager& objMgr;
		GraphicsManager& gfxMgr;

		TileSet tileSet;
		std::vector<TileType> collidableList;
		std::map<std::pair<int, int>, Tile> map;
	};
}