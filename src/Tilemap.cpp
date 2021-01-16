#include "Tilemap.h"
#include "Utils.h"

void StarBangBang::Tilemap::Init()
{
	tileWidth = 100;
	tileHeight = 100;

	mapWidth = 20;
	mapHeight = 1;

	tileImage.Init("../Resources/grass.png", tileWidth, tileHeight, 1);
	collider.Init(tileWidth * mapWidth, tileHeight * mapHeight);

	transform.position.x -= AEGetWindowWidth() / 2;
	transform.position.y -= AEGetWindowHeight() / 2 - tileHeight / 4;

	for (int i = 0; i < mapHeight; i++)
	{
		std::vector<Tile> row;
		for (int j = 0; j < mapWidth; j++)
		{
			Tile tile;
			AEVec2 pos;
			pos.x = (float)j;
			pos.y = (float)i;

			tile.Init(&tileImage, pos);
			row.push_back(tile);
		}
		tiles.push_back(row);
	}
}

void StarBangBang::Tilemap::Update()
{
	drag.Update(transform.position, GetMouseWorldPos(), collider.width, collider.height);
}

void StarBangBang::Tilemap::Draw()
{
	for (std::vector<Tile> row : tiles)
	{
		for (Tile tile : row)
		{
			tile.Draw(transform.position, tileWidth, tileHeight);
		}
	}
}

void StarBangBang::Tilemap::Exit()
{
	tileImage.Exit();
}
