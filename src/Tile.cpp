#include "Tile.h"

TempTeam::Tile::Tile()
{
	image = nullptr;
	position.x = 0;
	position.y = 0;
}

void TempTeam::Tile::Init(Image* image)
{
	this->image = image;
}

void TempTeam::Tile::Update()
{

}

void TempTeam::Tile::Draw(AEVec2 mapPos, float width, float height)
{
	AEVec2 worldPos;
	worldPos.x = mapPos.x + position.x * width;
	worldPos.x = mapPos.y + position.y * height;
	image->Draw(worldPos);
}

void TempTeam::Tile::Exit()
{
}
