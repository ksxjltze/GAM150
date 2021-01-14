#include "Tilemap.h"

void TempTeam::Tilemap::Init()
{
	tileImage.Init("../Resources/grass.png", 50, 50, 255);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			tiles[i][j].Init(&tileImage);
		}
	}
}

void TempTeam::Tilemap::Update()
{

}

void TempTeam::Tilemap::Draw()
{
	for (std::vector<Tile> row : tiles)
	{
		for (Tile tile : row)
		{
			tile.Draw(transform.position, 50, 50);
		}
	}
}

void TempTeam::Tilemap::Exit()
{
}
