#pragma once
#include "ObjectManager.h"

namespace StarBangBang
{
	class TileManager
	{
	public:
		void Init(ObjectManager &objectManager, GraphicsManager& graphicsManager);
	private:
		GameObject* tilemap;
		std::vector <std::vector<GameObject*>> tiles;
		float tileWidth = 100;
		float tileHeight = 100;

		int mapWidth = 20;
		int mapHeight = 1;
	};
}