#include "Level_Demo.h"
#include "CameraComponent.h"

#include "InteractableComponent.h"
#include "Guard.h"

#include <iostream>
#include "constants.h"

StarBangBang::Level_Demo::Level_Demo(GameStateManager* manager, int id) : State(id)
{
	player = nullptr;
	player2 = nullptr;

	movementController = nullptr;

	testGuard = nullptr;
	testInteractable = nullptr;

	gameStateManager = manager;
}

void StarBangBang::Level_Demo::Load()
{
	playerImage = graphicsManager.CreateSprite("../Resources/boi.png");
	player2Image = graphicsManager.CreateSprite("../Resources/boi2.png");
	planetImage = graphicsManager.CreateSprite("../Resources/PlanetTexture.png");

}

//Initialization of game objects, components and scripts.
void StarBangBang::Level_Demo::Init()
{
	GameObject* worldOriginMarker = objectManager.NewGameObject();
	player = objectManager.NewGameObject();
	testGuard = objectManager.NewGameObject();
	movementController = objectManager.NewGameObject();

	objectManager.AddImage(worldOriginMarker, planetImage);
	objectManager.AddImage(player, playerImage);
	objectManager.AddImage(testGuard, playerImage);

	//Creates a clone of the player gameObject and changes the sprite texture.
	player2 = objectManager.CloneGameObject(player);
	player2->GetComponent<ImageComponent>()->SetTexture(player2Image.texture);

	testInteractable = objectManager.CloneGameObject(player2);

	player->SetPos({ 200, 200 });
	player2->SetPos({ -200, 200 });
	testInteractable->SetPos({ 50, 50 });

	objectManager.AddComponent<CameraComponent>(player);
	objectManager.AddComponent<InteractableComponent>(testInteractable);

	objectManager.AddScript<Guard>(testGuard);
	objectManager.AddScript<GuardMovement>(testGuard);
	objectManager.AddScript<PrimaryMovementController>(player);
	objectManager.AddScript<SecondaryMovementController>(player2);

	testInteractable->GetComponent<InteractableComponent>()->SetType(InteractableComponent::INTERACTABLE_TYPE::TYPE_PRINTER);

	//Testing Tags
	tagManager.AddTag(*player, "Test");
	tagManager.GetGameObjectByTag("Test").transform.scale = { 2, 2 };

	//Scale test
	worldOriginMarker->transform.scale = { 0.5, 0.5 };
	testObjects.push_back(worldOriginMarker);

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
	State::Free();
}

void StarBangBang::Level_Demo::Unload()
{

}
