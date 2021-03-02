#pragma once
#include "GraphicsManager.h"
#include <map>

namespace StarBangBang
{
	enum class TileType
	{
		GRASS, STONE
	};

	struct TileTexture
	{
		AEGfxTexture* texture;
		TileType type;
	};

	class TileSet
	{
	public:
		void Load(std::string path);
	private:
		std::map<TileType, TileTexture> set;
	};
}