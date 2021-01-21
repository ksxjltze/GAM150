#include "Level_Demo.h"
#include "CameraComponent.h"
#include "InteractableComponent.h"

StarBangBang::Level_Demo::Level_Demo(GameStateManager* manager, int id) : State(id)
{
	player = nullptr;
	player2 = nullptr;
	testInteractable = nullptr;
	gameStateManager = manager;
}

void StarBangBang::Level_Demo::Load()
{
	playerImage.texture = graphicsManager.LoadTexture("../Resources/boi.png");
	player2Image.texture = graphicsManager.LoadTexture("../Resources/boi2.png");
	planetImage.texture = graphicsManager.LoadTexture("../Resources/PlanetTexture.png");

	playerImage.mesh = graphicsManager.CreateMesh(100, 100);
	planetImage.mesh = graphicsManager.CreateMesh(100, 100);
	player2Image.mesh = graphicsManager.CreateMesh(100, 100);
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

	testInteractable = objectManager.CloneGameObject(player);
	testInteractable->SetPos({ 50, 50 });
	objectManager.AddComponent<InteractableComponent>(testInteractable);
	testInteractable->GetComponent<InteractableComponent>()->SetType(InteractableComponent::INTERACTABLE_TYPE::TYPE_PRINTER);

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
