#include "Level_Demo.h"
#include "CameraComponent.h"

#include "InteractableComponent.h"
#include "Guard.h"
#include "GuardManager.h"
#include "SecurityCamera.h"
#include "Detector.h"
#include "Map.h"

#include "MovementManager.h"
#include "DetectionListener.h"
#include "MessageBus.h"

#include <iostream>
#include "constants.h"

#include "ObserverTest.h"
#include "Text.h"
#include "globals.h"

StarBangBang::Level_Demo::Level_Demo(int id, GameStateManager& manager) : Scene(id, manager), tilemap{ objectManager, graphicsManager }
{
	player = nullptr;
	player2 = nullptr;
	map = nullptr;
	testSecurityCam = nullptr;

	movementController = nullptr;

	testInteractable = nullptr;
	guardManager = nullptr;
}

void StarBangBang::Level_Demo::Load()
{
	//playerImage = graphicsManager.CreateSprite("./Resources/boi.png");
	//player2Image = graphicsManager.CreateSprite("./Resources/boi2.png");
	playerImage = graphicsManager.CreateSprite(RESOURCES::CAPTAINSTEALTH_F1_PATH);
	player2Image = graphicsManager.CreateSprite(RESOURCES::PRISONER_F1_PATH);
	planetImage = graphicsManager.CreateSprite("./Resources/PlanetTexture.png");
	//guardImage = graphicsManager.CreateSprite("./Resources/guard.png");
	guardImage = graphicsManager.CreateSprite(RESOURCES::SECURITYGUARD_F1_PATH);
	//securityCamImage = graphicsManager.CreateSprite("./Resources/guard.png");
	securityCamImage = graphicsManager.CreateSprite(RESOURCES::SECURITYGUARD_F1_PATH);
	mapImage = graphicsManager.CreateSprite("./Resources/map.png");
}

//Initialization of game objects, components and scripts.
void StarBangBang::Level_Demo::Init()
{
	PathFinder::ShowGrid(true);
	GRAPHICS::SetBackgroundColor(Black);
	tilemap.Load(RESOURCES::LEVELS::LEVEL_TEST_PATH);

	GameObject* worldOriginMarker = objectManager.NewGameObject();
	player = objectManager.NewGameObject();
	DetectionListener* listener = &objectManager.AddComponent<DetectionListener>(player);
	MessageBus::RegisterListener(listener);
	
	movementController = objectManager.NewGameObject();

	objectManager.AddImage(worldOriginMarker, planetImage);
	objectManager.AddImage(player, playerImage);
	objectManager.AddComponent<Text>(player);
	Text* txt = player->GetComponent<Text>();
	assert(txt);
	txt->fontID = StarBangBang::fontId;


	guardManager = objectManager.NewGameObject();
	objectManager.AddComponent<GuardManager>(guardManager).Init(&objectManager, &guardImage, player, player2);

	testSecurityCam = objectManager.NewGameObject();
	objectManager.AddImage(testSecurityCam, securityCamImage);
	objectManager.AddComponent<SecurityCamera>(testSecurityCam).SetRotationMinMax(-90.f, 90.f);
	objectManager.AddComponent<Detector>(testSecurityCam);
	testSecurityCam->GetComponent<Detector>()->Init(90.f, 250.f, player);
	testSecurityCam->SetPos({ 100, 750 });

	map = objectManager.NewGameObject();
	objectManager.AddImage(map, mapImage);
	map->transform.scale = { 5.f, 5.f };
	objectManager.AddComponent<Map>(map).Init(tilemap.GetMapWidth(), tilemap.GetMapHeight(), player, &objectManager, &playerImage);

	//Creates a clone of the player gameObject and changes the sprite texture.
	player2 = objectManager.CloneGameObject(player);
	player2->GetComponent<ImageComponent>()->SetTexture(player2Image.texture);

	testInteractable = objectManager.CloneGameObject(player2);

	player->SetPos({ 250, 750 }); //200, 200
	player2->SetPos({ -150, 200 });
	testInteractable->SetPos({ 50, 50 });

	objectManager.AddComponent<CameraComponent>(player);
	objectManager.AddComponent<InteractableComponent>(testInteractable);

	objectManager.AddComponent<Movement>(player);
	objectManager.AddComponent<Movement>(player2);
	objectManager.AddComponent<MovementManager>(movementController);
	//objectManager.AddComponent<SecondaryMovementController>(testInteractable);

	movementController->GetComponent<MovementManager>()->AddController(player);
	movementController->GetComponent<MovementManager>()->AddController(player2);
	//testInteractable->GetComponent<InteractableComponent>()->SetType(InteractableComponent::INTERACTABLE_TYPE::TYPE_PRINTER);

	//Testing Tags
	tagManager.AddTag(*player, "Test");
	tagManager.GetGameObjectByTag("Test").transform.scale = { 0.9f, 0.9f };

	//Scale test
	worldOriginMarker->transform.scale = { 0.5, 0.5 };
	testObjects.push_back(worldOriginMarker);

	objectManager.Init();
}

void StarBangBang::Level_Demo::Update()
{
	Scene::Update();
	if (AEInputCheckTriggered(VK_SPACE))
	{
		gameStateManager.SetNextGameState(SceneID::EDITOR);
	}

	if (AEInputCheckTriggered(AEVK_M))
	{
		map->active = !map->active;

		// send message to player so he can't move
		// ...
	}
}

void StarBangBang::Level_Demo::Draw()
{
	Scene::Draw();

}

void StarBangBang::Level_Demo::Free()
{
	Scene::Free();
}

void StarBangBang::Level_Demo::Unload()
{
	tilemap.Unload();
	Scene::Unload();
}
