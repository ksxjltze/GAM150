#include "TileManager.h"

StarBangBang::TileManager::TileManager()
{
	tilemapGameObject = nullptr; 

	tileWidth = 100;
	tileHeight = 100;

	mapWidth = 20;
	mapHeight = 1;
}

void StarBangBang::TileManager::Load(GraphicsManager& graphicsManager)
{
	tileSprite.texture = graphicsManager.LoadTexture("../Resources/grass.png");
	tileSprite.mesh = graphicsManager.CreateMesh(tileWidth, tileHeight);
}

StarBangBang::GameObject* StarBangBang::TileManager::Init(ObjectManager& objectManager, GraphicsManager& graphicsManager)
{
	tilemapGameObject = objectManager.NewGameObject();
	tilemapGameObject->transform.position.y -= AEGetWindowHeight() / 2;
	tilemapGameObject->transform.position.x -= AEGetWindowWidth() / 2;

	for (int i = 0; i < mapHeight; i++)
	{
		std::vector<GameObject*> row;
		for (int j = 0; j < mapWidth; j++)
		{
			AEVec2 pos;
			pos.x = (float)j * tileWidth;
			pos.y = (float)i * tileHeight;

			GameObject* tile = objectManager.NewGameObject();
			objectManager.AddChildGameObject(tile, tilemapGameObject);
			objectManager.AddImageComponent(tile, tileSprite.texture, tileSprite.mesh);
			tile->transform.position = pos;
			row.push_back(tile);
		}
		tiles.push_back(row);
	}
	return tilemapGameObject;

}

