#include "Tile.h"

TempTeam::Tile::Tile()
{
	image = nullptr;
	position.x = 0;
	position.y = 0;
}

void TempTeam::Tile::Init(Image* image, AEVec2 position)
{
	this->image = image;
	this->position = position;
}

void TempTeam::Tile::Update()
{

}

void TempTeam::Tile::Draw(AEVec2 mapPos, float width, float height)
{
	AEVec2 worldPos;
	worldPos.x = mapPos.x + position.x * width;
	worldPos.y = mapPos.y + position.y * height;
	image->Draw(worldPos);
}

void TempTeam::Tile::Exit()
{
}
