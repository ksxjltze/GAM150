#include "Map.h"
#include "ObjectManager.h"
#include "Sprite.h"

using namespace StarBangBang;

Map::Map(GameObject* gameObject)
	: Script(gameObject)
{
}

void Map::Start()
{
	gameObject->active = false;
}

void Map::Init(int mapWidth, int mapHeight, GameObject* _player, ObjectManager* objectManager, Sprite* sprite)
{
	width = mapWidth;
	height = mapHeight;
	player = _player;

	testIndicator = objectManager->NewGameObject();
	objectManager->AddImage(testIndicator, *sprite);
	testIndicator->transform.scale = { 0.2f, 0.2f };
}

void Map::Update()
{
	testIndicator->active = gameObject->active;

	// to show map in center of screen
	gameObject->SetPos(player->GetPos());

	testIndicator->SetPos(player->GetPos());
}

AEVec2 Map::GlobalToLocalCoord(AEVec2 pos)
{
	AEVec2 offset = player->GetPos();
	AEVec2 result{ 0, 0 };



	return result;
}