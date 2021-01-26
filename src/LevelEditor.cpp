#include "LevelEditor.h"

StarBangBang::LevelEditor::LevelEditor(GameStateManager* manager, int id) : State(id)
{
	gameStateManager = manager;
	tileWidth = 50; tileHeight = 50;
}

void StarBangBang::LevelEditor::Load()
{
	Sprite grassSprite = graphicsManager.CreateSprite(Constants::PROTOTYPE_SPRITE_GRASS_PATH, tileWidth, tileHeight);
	Sprite stoneSprite = graphicsManager.CreateSprite(Constants::PROTOTYPE_SPRITE_STONE_PATH, tileWidth, tileHeight);

	std::pair<std::string, Sprite> grassTile = std::pair<std::string, Sprite>("Grass", grassSprite);
	std::pair<std::string, Sprite> stoneTile = std::pair<std::string, Sprite>("Stone", stoneSprite);

	palette.insert(grassTile);
	palette.insert(stoneTile);
}

void StarBangBang::LevelEditor::Init()
{
	GameObject* obj = objectManager.NewGameObject();
	GameObject* obj2 = objectManager.NewGameObject();

	objectManager.AddImage(obj, palette.at("Grass"));
	objectManager.AddImage(obj2, palette.at("Stone"));

	obj2->transform.position.x += tileWidth;
}

void StarBangBang::LevelEditor::Update()
{
	State::Update();
}

void StarBangBang::LevelEditor::Draw()
{
	State::Draw();
}

void StarBangBang::LevelEditor::Free()
{
}

void StarBangBang::LevelEditor::Unload()
{
}
