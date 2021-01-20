#include "Level_Demo.h"
#include "CameraComponent.h"

StarBangBang::Level_Demo::Level_Demo(GameStateManager* manager, int id) : State(id)
{
	player = nullptr;
	gameStateManager = manager;
}

void StarBangBang::Level_Demo::Load()
{
	playerImage.texture = graphicsManager.LoadTexture("../Resources/boi.png");
	planetImage.texture = graphicsManager.LoadTexture("../Resources/PlanetTexture.png");
	playerImage.mesh = graphicsManager.CreateMesh(100, 100);
	planetImage.mesh = graphicsManager.CreateMesh(100, 100);
}

void StarBangBang::Level_Demo::Init()
{
	player = objectManager.NewGameObject(100, 100);
	objectManager.AddImageComponent(player, playerImage);
	scriptManager.AddScript<Player>(player);
	player->transform.position.x = 200;

	GameObject* worldOriginMarker = objectManager.NewGameObject();
	objectManager.AddImageComponent(worldOriginMarker, planetImage);
	testObjects.push_back(worldOriginMarker);

	for (int i = 0; i < 10; i++)
	{
		GameObject* testObject = objectManager.CloneGameObject(player);
		objectManager.AddComponent<DragComponent>(testObject);
		testObjects[i]->transform.position.x += i * 50;
		testObjects[i]->transform.position.y += i % 3 * 100;

		testObjects.push_back(testObject);
	}

	player->transform.position.y = 200;

	objectManager.AddComponent<CameraComponent>(player);

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
