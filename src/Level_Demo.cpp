#include "Level_Demo.h"
#include "CameraComponent.h"

#include "InteractableComponent.h"
#include "Guard.h"
#include "GuardManager.h"
#include "SecurityCamera.h"
#include "Detector.h"

#include "DetectionListener.h"
#include "CollisionListener.h"

#include <iostream>
#include "constants.h"

#include "ObserverTest.h"
#include "Text.h"
#include "globals.h"


#include "CaptainStealth.h"


namespace StarBangBang
{
	Sprite computerSprite;
	Sprite doorSprite;

	StarBangBang::BoxCollider* playerCol;
	StarBangBang::BoxCollider* clientCol;

	StarBangBang::Level_Demo::Level_Demo(int id, GameStateManager& manager) : Scene(id, manager), tilemap{ objectManager, graphicsManager }
	{
		player = nullptr;
		player2 = nullptr;
		movementController = nullptr;
		guardManager = nullptr;
	}

	void StarBangBang::Level_Demo::Load()
	{
		playerImage = graphicsManager.CreateSprite(RESOURCES::CAPTAINSTEALTH_F1_PATH);
		player2Image = graphicsManager.CreateSprite(RESOURCES::PRISONER_F1_PATH);
		guardImage = graphicsManager.CreateSprite(RESOURCES::SECURITYGUARD_F1_PATH);
		securityCamImage = graphicsManager.CreateSprite(RESOURCES::CAMERA_PATH);
		exitImage = graphicsManager.CreateSprite(RESOURCES::VENDING_LEFT_PATH);
		computerSprite = graphicsManager.CreateSprite(RESOURCES::COMPUTER_PATH);
		doorSprite = graphicsManager.CreateSprite(RESOURCES::DOOR_PATH);
	}

	//Initialization of game objects, components and scripts.
	void StarBangBang::Level_Demo::Init()
	{
		PathFinder::ShowGrid(true);
		GRAPHICS::SetBackgroundColor(Black);

		//Load tilemap
		tilemap.SetCollidableTypes({ TileType::BRICK_BLACK });
		tilemap.Load(RESOURCES::LEVELS::LEVEL_TEST_PATH);

		tilemap.SetGrid(PathFinder::GetWorldGrid());
		//tilemap.SetVisible(false);

		//Movement controller
		movementController = objectManager.NewGameObject();
		MovementManager& moveMgr = objectManager.AddComponent<MovementManager>(movementController);

		//Player components and scripts
		CaptainStealth::SpawnPlayer(objectManager, player, playerImage);

		//Client
		CaptainStealth::SpawnClient(objectManager, player2, player2Image);

		//Compooter
		srand(time(NULL));
		for (int i = 0; i < 7; ++i)
		{
			Grid& grid = PathFinder::GetWorldGrid();
			A_Node n = grid.GetRandomFreeNode();
			CaptainStealth::SpawnComputer(objectManager, computerSprite, n.nodePos);
		}

		//Movement Manager
		moveMgr.AddController(player);
		moveMgr.AddController(player2);

		//Guards and security cameras
		guardManager = objectManager.NewGameObject();
		GuardManager& mgr = objectManager.AddComponent<GuardManager>(guardManager);
		mgr.Init(&objectManager, &guardImage, player, player2);
		guardManager->GetComponent<GuardManager>()->CreateSecurityCameras(&objectManager, &securityCamImage, player, player2);

		//serve as references parameter for raycast ignore
		playerCol = player->GetComponent<BoxCollider>();
		clientCol = player2->GetComponent<BoxCollider>();

		//Level Exit
		GameObject* exit = objectManager.NewGameObject();
		//temp
		exit->transform.position = tilemap.GetPositionAtIndex(10, 40);
		exit->name = "EXIT";

		CaptainStealth::SpawnDoor(objectManager, doorSprite, exit->transform.position);

		objectManager.AddImage(exit, exitImage);
		objectManager.AddCollider(exit, true).isTrigger = true;
	

		// Call Start on scripts
		objectManager.Init();
	}

	void StarBangBang::Level_Demo::Update()
	{
		Scene::Update();
		if (AEInputCheckTriggered(VK_SPACE))
		{
			gameStateManager.SetNextGameState(SceneID::EDITOR);
		}

		PlayerScript* playerScript = player->GetComponent<PlayerScript>();
		if (playerScript->isGameOver())
		{
			std::cout << "LOSE\n" << std::endl;
			gameStateManager.SetNextGameState(MAIN_MENU);
		}
		else if (playerScript->isWin())
		{
			std::cout << "WIN\n" << std::endl;
			gameStateManager.SetNextGameState(MAIN_MENU);
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

}