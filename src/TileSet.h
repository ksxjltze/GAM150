#pragma once
#include "GraphicsManager.h"
#include <map>

namespace StarBangBang
{
	enum class TileType
	{
		NONE = 0,
		GRASS,
		STONE,
		BRICK_BLACK,
		FLOOR_PRISON,
		FLOOR_PRISON2,
		BRICK_RED,
		END,
		TEST = 11
	};

	struct TileSprite
	{
		Sprite sprite;
		TileType type;
	};

	class TileSet
	{
	public:
		void Load(GraphicsManager&);
		void LoadTileSprite(GraphicsManager&, TileType type, const std::string& path);
		void Clear();
		const std::string& GetTileTypeName(TileType type);
		const TileSprite& GetTileSprite(TileType);
	private:
		std::map<TileType, TileSprite> set;
	};

	TileType& operator++(TileType& tileType);
	TileType operator++(TileType& tileType, int);
}