#include "TileManager.h"
#include <algorithm>
#include "Utils.h"

StarBangBang::TileManager::TileManager(ObjectManager* manager)
{
	tilemapGameObject = nullptr;
	objectManager = manager;

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

StarBangBang::GameObject* StarBangBang::TileManager::Init(GraphicsManager& graphicsManager)
{
	tilemapGameObject = objectManager->NewGameObject(tileWidth * mapWidth, tileHeight * mapHeight);
	tilemapGameObject->transform.position.y -= AEGetWindowHeight() / 2;
	tilemapGameObject->transform.position.x -= AEGetWindowWidth() / 2;

	tiles.reserve(mapHeight);
	for (std::vector<GameObject*> row : tiles)
	{
		row.reserve(mapWidth);
	}

	//TODO: Load from file
	for (int i = 0; i < mapHeight; i++)
	{
		std::vector<GameObject*> row;
		for (int j = 0; j < mapWidth; j++)
		{
			AEVec2 pos;
			pos.x = (float)j * tileWidth;
			pos.y = (float)i * tileHeight;

			GameObject* tile = objectManager->NewGameObject(tileWidth, tileHeight);
			objectManager->AddChildGameObject(tile, tilemapGameObject);
			objectManager->AddImageComponent(tile, tileSprite.texture, tileSprite.mesh);
			tile->transform.position = pos;
			row.push_back(tile);
		}
		tiles.push_back(row);
	}
	return tilemapGameObject;

}

void StarBangBang::TileManager::AddTile(int gridX, int gridY)
{
	GameObject* tile = objectManager->NewGameObject(tileWidth, tileHeight);
	tile->transform.position.x *= tileWidth;
	tile->transform.position.y *= tileHeight;
	objectManager->AddImageComponent(tile, tileSprite.texture, tileSprite.mesh);
	objectManager->AddChildGameObject(tile, tilemapGameObject);

	std::vector<GameObject*> row;
	row.reserve(mapWidth);

	if (gridY >= mapHeight)
	{
		for (int i = mapHeight; i <= gridY; i++)
		{
			tiles.push_back(row);
		}
	}

	row = tiles[gridY];
	row.push_back(tile);
	std::sort(row.begin(), row.end(), CompareGameObject);
}

