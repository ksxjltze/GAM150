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
	testSprite = graphicsManager.CreateSprite(Constants::PROTOTYPE_SPRITE_1_PATH, 100, 100);
}

void StarBangBang::TestScene::Init()
{
	GameObject* obj = objectManager.NewGameObject();
	GameObject* obj2 = objectManager.NewGameObject();

	objectManager.AddImageComponent(obj, testSprite);
	objectManager.AddScriptComponent<EventTest>(obj);
	objectManager.AddScriptComponent<ObserverTest>(obj2);

	obj->GetComponent<EventTest>()->subject.addObserver(obj2->GetComponent<ObserverTest>());
	gameObjects.push_back(obj);
	scriptManager.Start();
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
