#pragma once
#include "ObjectManager.h"
//DEPRECATED
//REDO

namespace StarBangBang
{
	class TileManager
	{
	public:
		TileManager(ObjectManager* manager);
		GameObject* Init(GraphicsManager& graphicsManager);
		void AddTile(int gridX, int gridY);
		void Load(GraphicsManager& graphicsManager);
	private:
		std::vector <std::vector<GameObject*>> tiles;
		GameObject* tilemapGameObject;
		ObjectManager* objectManager;
		Sprite tileSprite;
		float tileWidth;
		float tileHeight;

		int mapWidth;
		int mapHeight;
	};
}