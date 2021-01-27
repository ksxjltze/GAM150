#include "TestScene.h"
#include "constants.h"
#include "EventTest.h"
#include "ObserverTest.h"

StarBangBang::TestScene::TestScene(GameStateManager* manager, int id) : State(id)
{
	gameStateManager = manager;
}

void StarBangBang::TestScene::Load()
{
	testSprite = graphicsManager.CreateSprite(Constants::PROTOTYPE_SPRITE_2_PATH);
}

void StarBangBang::TestScene::Init()
{
	GameObject* obj = objectManager.NewGameObject();
	GameObject* obj2 = objectManager.NewGameObject();

	objectManager.AddImage(obj, testSprite);
	objectManager.AddImage(obj2, testSprite);

	obj->transform.position.x = 100;
	obj2->transform.position.x = -100;

	obj->transform.rotation = 90;
	obj2->transform.rotation = -90;

	obj->transform.scale = { 1, 2 };
	obj->transform.scale = { 2, 1 };

	objectManager.Init();
}

void StarBangBang::TestScene::Update()
{
	State::Update();
	if (AEInputCheckTriggered(VK_SPACE))
	{
		gameStateManager->SetNextGameState(Constants::SceneID::DEMO);
	}
}

void StarBangBang::TestScene::Draw()
{
	State::Draw();
}

void StarBangBang::TestScene::Free()
{
	State::Free();
}

void StarBangBang::TestScene::Unload()
{
	State::Unload();
}
