#include "Level_Demo.h"
#include "CameraComponent.h"

#include "InteractableComponent.h"
#include "Guard.h"

#include "MovementManager.h"

#include <iostream>
#include "constants.h"

#include "ObserverTest.h"
#include "EventTest.h"

StarBangBang::Level_Demo::Level_Demo(int id, GameStateManager& manager) : Scene(id, manager)
{
	player = nullptr;
	player2 = nullptr;

	movementController = nullptr;

	testGuard = nullptr;
	testInteractable = nullptr;
	guardManager = nullptr;
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
	tilemap.Load(RESOURCES::LEVEL_TEST_PATH, objectManager, graphicsManager);

	GameObject* worldOriginMarker = objectManager.NewGameObject();
	player = objectManager.NewGameObject();
	movementController = objectManager.NewGameObject();

	objectManager.AddImage(worldOriginMarker, planetImage);
	objectManager.AddImage(player, playerImage);

	guardManager = objectManager.NewGameObject();
	objectManager.AddComponent<GuardManager>(guardManager);
	guardManager->GetComponent<GuardManager>()->SetObjectManager(&objectManager);
	guardManager->GetComponent<GuardManager>()->SetSprite(&playerImage);
	guardManager->GetComponent<GuardManager>()->Init();

	//Creates a clone of the player gameObject and changes the sprite texture.
	player2 = objectManager.CloneGameObject(player);
	player2->GetComponent<ImageComponent>()->SetTexture(player2Image.texture);

	testInteractable = objectManager.CloneGameObject(player2);

	player->SetPos({ 200, 200 });
	player2->SetPos({ -150, 200 });
	testInteractable->SetPos({ 50, 50 });

	objectManager.AddComponent<CameraComponent>(player);
	objectManager.AddComponent<InteractableComponent>(testInteractable);

	objectManager.AddComponent<PrimaryMovementController>(player);
	objectManager.AddComponent<PrimaryMovementController>(player2);
	objectManager.AddComponent<MovementManager>(movementController);
	objectManager.AddComponent<SecondaryMovementController>(testInteractable);

	movementController->GetComponent<MovementManager>()->AddController(player);
	movementController->GetComponent<MovementManager>()->AddController(player2);
	testInteractable->GetComponent<InteractableComponent>()->SetType(InteractableComponent::INTERACTABLE_TYPE::TYPE_PRINTER);

	//Testing Tags
	tagManager.AddTag(*player, "Test");
	tagManager.GetGameObjectByTag("Test").transform.scale = { 2, 2 };

	//Scale test
	worldOriginMarker->transform.scale = { 0.5, 0.5 };
	testObjects.push_back(worldOriginMarker);

	objectManager.AddComponent<EventTest>(player);
	objectManager.AddComponent<ObserverTest>(player2);

	EventTest* test = player->GetComponent<EventTest>();
	ObserverTest* obs = player2->GetComponent<ObserverTest>();
	test->subject.addObserver(obs);

	objectManager.Init();
}

void StarBangBang::Level_Demo::Update()
{
	Scene::Update();
	if (AEInputCheckTriggered(VK_SPACE))
	{
		gameStateManager.SetNextGameState(SCENE::EDITOR);
	}
}

void StarBangBang::Level_Demo::Draw()
{
	Scene::Draw();

}

void StarBangBang::Level_Demo::Free()
{
	//delete guardManager;
	Scene::Free();
}

void StarBangBang::Level_Demo::Unload()
{
	Scene::Unload();
}
