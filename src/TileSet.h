#pragma once
#include "GraphicsManager.h"
#include <map>

namespace StarBangBang
{
	enum class TileType
	{
		GRASS = 1, STONE
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

		TileSprite GetTileSprite(TileType);
	private:
		std::map<TileType, TileSprite> set;
	};
}