#include "TestScene.h"
#include "constants.h"

StarBangBang::TestScene::TestScene(GameStateManager* manager, int id) : State(id)
{
	gameStateManager = manager;
}

void StarBangBang::TestScene::Load()
{
	testSprite = graphicsManager.CreateSprite(Constants::PROTOTYPE_SPRITE_1_PATH, 100, 100);
}

void StarBangBang::TestScene::Init()
{
	GameObject* obj = objectManager.NewGameObject();
	objectManager.AddImageComponent(obj, testSprite);
	gameObjects.push_back(obj);
}

void StarBangBang::TestScene::Update()
{
	State::Update();
}

void StarBangBang::TestScene::Draw()
{
	State::Draw();
}

void StarBangBang::TestScene::Free()
{

}

void StarBangBang::TestScene::Unload()
{

}
