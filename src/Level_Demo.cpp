#include "Level_Demo.h"
#include "CameraComponent.h"

#include "InteractableComponent.h"

#include <iostream>
#include "constants.h"

StarBangBang::Level_Demo::Level_Demo(GameStateManager* manager, int id) : State(id)
{
	player = nullptr;
	player2 = nullptr;
	testInteractable = nullptr;
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
	objectManager.AddImage(player, playerImage);
	objectManager.AddScript<PrimaryMovementController>(player);

	tagManager.AddTag(*player, "Test");

	//Player 2
	player2 = objectManager.CloneGameObject(player);
	player2->GetComponent<ImageComponent>()->SetTexture(player2Image.texture); // testing
	objectManager.AddScript<SecondaryMovementController>(player2);

	//Script Clone Test
	testObjects.push_back(objectManager.CloneGameObject(player2));
	testObjects.back()->transform.position.x = 200;
	objectManager.AddComponent<DragComponent>(testObjects.back());

	player->transform.position.x = 200;
	player2->transform.position.x = -100;

	testInteractable = objectManager.CloneGameObject(player);
	testInteractable->SetPos({ 50, 50 });
	objectManager.AddComponent<InteractableComponent>(testInteractable);
	testInteractable->GetComponent<InteractableComponent>()->SetType(InteractableComponent::INTERACTABLE_TYPE::TYPE_PRINTER);

	GameObject* worldOriginMarker = objectManager.NewGameObject();
	objectManager.AddImage(worldOriginMarker, planetImage);
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

	tagManager.GetGameObjectByTag("Test").transform.scale = { 10, 2 };
	tagManager.GetGameObjectByTag("Test").transform.rotation = 69;

	objectManager.AddComponent<CameraComponent>(player);
	scriptManager.Start();
}

void StarBangBang::Level_Demo::Update()
{
	State::Update();
	if (AEInputCheckTriggered(VK_SPACE))
	{
		gameStateManager->SetNextGameState(Constants::SceneID::TEST);
	}
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
