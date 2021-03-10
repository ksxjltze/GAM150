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
		BRICK_RED, 
		FLOOR_PRISON, 
		FLOOR_OFFICE, 
		END
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

		const TileSprite& GetTileSprite(TileType);
	private:
		std::map<TileType, TileSprite> set;
	};

	TileType& operator++(TileType& tileType);
	TileType operator++(TileType& tileType, int);
}