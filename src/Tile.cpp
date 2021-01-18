#include "Tile.h"

StarBangBang::Tile::Tile()
{
	image = nullptr;
	position.x = 0;
	position.y = 0;
}

void StarBangBang::Tile::Init(Image* image, AEVec2 position)
{
	this->image = image;
	this->position = position;
}

void StarBangBang::Tile::Update()
{

}

void StarBangBang::Tile::Draw(AEVec2 mapPos, float width, float height)
{
	AEVec2 worldPos;
	worldPos.x = mapPos.x + position.x * width;
	worldPos.y = mapPos.y + position.y * height;
	image->Draw(worldPos);
}

void StarBangBang::Tile::Exit()
{
}
