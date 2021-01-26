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
	testInteractable = nullptr;
	testGuard = nullptr;
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
	GameObject* worldOriginMarker = objectManager.NewGameObject();
	testObjects.push_back(worldOriginMarker);

	//Player 1
	player = objectManager.NewGameObject(100, 100);

	//Player 2
	player2 = objectManager.CloneGameObject(player);

	// Interactable test
	testInteractable = objectManager.CloneGameObject(player);

	// Guard test
	testGuard = objectManager.NewGameObject(0, 0);

	objectManager.AddImage(worldOriginMarker, planetImage);
	objectManager.AddImage(player, playerImage);
	objectManager.AddImage(player2, player2Image);
	objectManager.AddImage(testInteractable, playerImage);
	objectManager.AddImage(testGuard, playerImage);

	testInteractable->SetPos({ 50, 50 });
	player->SetPos({ 200, 200 });
	player2->SetPos({ -200, 200 });

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
