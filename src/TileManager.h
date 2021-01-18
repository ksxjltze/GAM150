#pragma once
#include "ObjectManager.h"

namespace StarBangBang
{
	class TileManager
	{
	public:
		TileManager();
		void Init(ObjectManager &objectManager, GraphicsManager& graphicsManager);
	private:
		GameObject* tilemapGameObject;
		std::vector <std::vector<GameObject*>> tiles;
		float tileWidth;
		float tileHeight;

		int mapWidth;
		int mapHeight;
	};
}