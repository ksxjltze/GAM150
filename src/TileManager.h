#pragma once
#include "ObjectManager.h"

namespace StarBangBang
{
	class TileManager
	{
	public:
		TileManager();
		GameObject* Init(ObjectManager &objectManager, GraphicsManager& graphicsManager);
		void Load(GraphicsManager& graphicsManager);
	private:
		std::vector <std::vector<GameObject*>> tiles;
		GameObject* tilemapGameObject;
		Sprite tileSprite;
		float tileWidth;
		float tileHeight;

		int mapWidth;
		int mapHeight;
	};
}