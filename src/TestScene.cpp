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
	testSprite = graphicsManager.CreateSprite(Constants::PROTOTYPE_SPRITE_2_PATH, 100, 100);
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

	//Event, Observer, Subject Test
	//objectManager.AddScript<EventTest>(obj);
	//objectManager.AddScript<ObserverTest>(obj2);
	//obj->transform.position.x -= AEGetWindowWidth() / 4;
	//gameObjects.push_back(obj);
	//ObserverTest* obsTest = obj2->GetComponent<ObserverTest>();

	//for (int i = 0; i < 10; i++)
	//{
	//	for (int j = 0; j < 10; j++)
	//	{
	//		GameObject* newObj = objectManager.CloneGameObject(obj);
	//		newObj->transform.position.x = obj->transform.position.x + j * 50;
	//		newObj->transform.position.y = obj->transform.position.y + i * 50;
	//		gameObjects.push_back(newObj);
	//		EventTest* test = newObj->GetComponent<EventTest>();
	//		test->subject.addObserver(obsTest);

	//	}
	//}

	scriptManager.Start();
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