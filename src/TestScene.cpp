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

	objectManager.AddImage(obj, testSprite);
	objectManager.AddScript<EventTest>(obj);
	objectManager.AddScript<ObserverTest>(obj2);
	obj->transform.position.x -= AEGetWindowWidth() / 4;
	gameObjects.push_back(obj);
	ObserverTest* obsTest = obj2->GetComponent<ObserverTest>();

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			GameObject* newObj = objectManager.CloneGameObject(obj);
			newObj->transform.position.x = obj->transform.position.x + j * 50;
			newObj->transform.position.y = obj->transform.position.y + i * 50;
			gameObjects.push_back(newObj);
			EventTest* test = newObj->GetComponent<EventTest>();
			test->subject.addObserver(obsTest);

		}
	}

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
