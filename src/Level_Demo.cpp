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

#include "Distractor.h"


#include "CaptainStealth.h"
#include "DebugText.h"

static bool god = false;


namespace StarBangBang
{
	Sprite computerSprite;
	Sprite doorSprite;
	Sprite boi;

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
		boi = graphicsManager.CreateSprite(RESOURCES::PROTOTYPE_SPRITE_2_PATH);
	}

	//Initialization of game objects, components and scripts.
	void StarBangBang::Level_Demo::Init()
	{
		god = false;
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
		player->transform.position = tilemap.GetPositionAtIndex(6, 3);

		//Client
		CaptainStealth::SpawnClient(objectManager, player2, player2Image);
		player2->transform.position = tilemap.GetPositionAtIndex(8, 3);

		//Compooter
		srand(static_cast<unsigned int>(time(NULL)));
		for (int i = 0; i < CONSTANTS::COMPUTER_COUNT; ++i)
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
		exit->transform.position = tilemap.GetPositionAtIndex(40, 45);
		exit->name = "EXIT";
		objectManager.AddImage(exit, exitImage);
		objectManager.AddCollider(exit, true).isTrigger = true;

		CaptainStealth::SpawnDoor(objectManager, doorSprite, exit->transform.position);

		//Distraction
		GameObject* distract = objectManager.NewGameObject();
		//temp
		distract->transform.position = tilemap.GetPositionAtIndex(8, 8);
		objectManager.AddComponent<Distractor>(distract);
		objectManager.AddImage(distract, boi);
		objectManager.AddCollider(distract, true).isTrigger = true;

		//Notification Text
		objectManager.AddComponent<DebugText>(objectManager.NewGameObject(), fontId);

		//Floating text
		MessageBus::Notify({ EventId::PRINT_TEXT, std::string("Find the Vending Machine!") });
		MessageBus::Notify({ EventId::PLAY_SOUND, "Test"});

	
	}

	void StarBangBang::Level_Demo::Update()
	{
		Scene::Update();
		if (AEInputCheckTriggered(VK_SPACE))
		{
			MessageBus::Notify({ EventId::PRINT_TEXT, std::string("Find the Exit!") });
		}

		if (AEInputCheckTriggered(AEVK_ESCAPE))
		{
			gameStateManager.SetNextGameState(MAIN_MENU);
		}

		if (AEInputCheckTriggered(AEVK_G))
		{
			if (!god)
			{
				god = true;
				MessageBus::Notify({ EventId::PRINT_TEXT, std::string("God Mode Enabled!") });
			}
			else
			{
				god = false;
				MessageBus::Notify({ EventId::PRINT_TEXT, std::string("God Mode Disabled!") });
			}
		}

		PlayerScript* playerScript = player->GetComponent<PlayerScript>();
		if (playerScript->isGameOver())
		{
			if (!god)
			{
				std::cout << "LOSE\n" << std::endl;
				gameStateManager.SetNextGameState(GAME_OVER);

			}
		}

		if (playerScript->isWin())
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