#include "Level_Demo.h"
#include "CameraComponent.h"

StarBangBang::Level_Demo::Level_Demo(GameStateManager* manager, int id) : State(id)
{
	player = nullptr;
	player2 = nullptr;
	gameStateManager = manager;
}

void StarBangBang::Level_Demo::Load()
{
	playerImage = graphicsManager.CreateSprite("../Resources/boi.png", 100, 100);
	player2Image = graphicsManager.CreateSprite("../Resources/boi2.png", 100, 100);
	planetImage = graphicsManager.CreateSprite("../Resources/PlanetTexture.png", 100, 100);

}

void StarBangBang::Level_Demo::Init()
{
	//Player 1
	player = objectManager.NewGameObject(100, 100);
	objectManager.AddImageComponent(player, playerImage);
	objectManager.AddScriptComponent<PrimaryMovementController>(player);

	//Player 2
	player2 = objectManager.CloneGameObject(player);
	player2->GetComponent<ImageComponent>()->SetTexture(player2Image.texture); // testing
	objectManager.AddScriptComponent<SecondaryMovementController>(player2);

	//Script Clone Test
	testObjects.push_back(objectManager.CloneGameObject(player2));
	testObjects.back()->transform.position.x = 200;

	player->transform.position.x = 200;
	player2->transform.position.x = -100;

	GameObject* worldOriginMarker = objectManager.NewGameObject();
	objectManager.AddImageComponent(worldOriginMarker, planetImage);
	testObjects.push_back(worldOriginMarker);

	//Mass Clone Test
	for (int i = 0; i < 10; i++)
	{
		GameObject* testObject = objectManager.CloneGameObject(player);
		objectManager.AddComponent<DragComponent>(testObject);
		testObjects[i]->transform.position.x += i * 50 + 500;
		testObjects[i]->transform.position.y += i % 3 * 100;

		testObjects.push_back(testObject);
	}

	player->transform.position.y = 200;
	player->transform.scale = { 2, 2 };
	player2->transform.position.y = 200;

	objectManager.AddComponent<CameraComponent>(player);
	scriptManager.Start();

}

void StarBangBang::Level_Demo::Update()
{
	State::Update();
}

void StarBangBang::Level_Demo::Draw()
{
	State::Draw();

}

void StarBangBang::Level_Demo::Free()
{

}

void StarBangBang::Level_Demo::Unload()
{

}
