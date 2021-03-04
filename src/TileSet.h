#pragma once
#include "GraphicsManager.h"
#include <map>

namespace StarBangBang
{
	enum class TileType
	{
		NONE = 0, GRASS, STONE, END = STONE
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
		void Load(const std::string& path);
		void Load(const std::string&& directoryPath);

		const TileSprite& GetTileSprite(TileType);
	private:
		std::map<TileType, TileSprite> set;
	};

	TileType& operator++(TileType& tileType);
	TileType operator++(TileType& tileType, int);
}