#include "LevelEditor.h"

StarBangBang::LevelEditor::LevelEditor(GameStateManager* manager, int id) : State(id)
{
	gameStateManager = manager;
	tileWidth = 50; tileHeight = 50;
}

void StarBangBang::LevelEditor::Load()
{
	Sprite grassSprite = graphicsManager.CreateSprite(Constants::PROTOTYPE_SPRITE_GRASS_PATH, tileWidth, tileHeight);
	std::pair<std::string, Sprite> grassTile = std::pair<std::string, Sprite>("Grass", grassSprite);
	palette.insert(grassTile);
}

void StarBangBang::LevelEditor::Init()
{
	GameObject* obj = objectManager.NewGameObject();
	objectManager.AddImage(obj, palette.at("Grass"));
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
