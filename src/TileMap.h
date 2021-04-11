/******************************************************************************/
/*!
\title		Captain Stealth
\file		TileMap.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		TileMap class.
			Responsible for loading tiles from the level data file.
			Or generating new tile maps.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include <map>
#include "ObjectManager.h"
#include "TileSet.h"
#include "Grid.h"

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
		void Fill(TileType type);
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
		AEVec2 GetPositionAtIndex(int x, int y);

		Tile& At(int x, int y);
		int GetMapWidth();
		int GetMapHeight();

		void SetGrid(Grid&);

		void Insert(int x, int y, TileType type);
		void Replace(int x, int y, TileType type);
		void Erase(int x, int y);

		Tile CreateNewTile(AEVec2 pos, TileSprite tileSprite, bool collidable = false);
		Tile ReplaceTile(Tile tile, AEVec2 pos, TileSprite tileSprite);

		void SetCollidableTypes(std::initializer_list<TileType> typeList);

	private:
		friend class LevelEditor;
		GameObject* base;
		float scale;
		int mapWidth, mapHeight;

		ObjectManager& objMgr;
		GraphicsManager& gfxMgr;

		TileSet tileSet;
		std::vector<TileType> collidableList;
		std::map<std::pair<int, int>, Tile> map;

	//Debug
	public:
		void SetVisible(bool visible);
	};
}