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
#include "time.h"
#include "GuardAnim.h"

#include "CaptainStealth.h"
#include "DebugText.h"

static bool god = false;
static float app_time = 0.0f;
static int animation_counter = 0;

enum class direction {idle = 0, left, right};
direction dir;

enum class current_char { fei_ge, prisoner };
current_char character;

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
		//forward player 1
		playerImage = graphicsManager.CreateSprite(RESOURCES::CAPTAINSTEALTH_F1_PATH);


		GuardAnim::Load(graphicsManager);

		//right animation player 1
		playerImageR1 = graphicsManager.CreateSprite(RESOURCES::CAPTAINSTEALTH_R1_PATH);
		playerImageR2 = graphicsManager.CreateSprite(RESOURCES::CAPTAINSTEALTH_R2_PATH);
		playerImageR3 = graphicsManager.CreateSprite(RESOURCES::CAPTAINSTEALTH_R3_PATH);

		//left animation for player 1 
		playerImageL1 = graphicsManager.CreateSprite(RESOURCES::CAPTAINSTEALTH_L1_PATH);
		playerImageL2 = graphicsManager.CreateSprite(RESOURCES::CAPTAINSTEALTH_L2_PATH);
		playerImageL3 = graphicsManager.CreateSprite(RESOURCES::CAPTAINSTEALTH_L3_PATH);

		//player 2
		player2Image = graphicsManager.CreateSprite(RESOURCES::PRISONER_F1_PATH);

		//right animation player 2
		playerImage2R1 = graphicsManager.CreateSprite(RESOURCES::PRISONER_R1_PATH);
		playerImage2R2 = graphicsManager.CreateSprite(RESOURCES::PRISONER_R2_PATH);
		playerImage2R3 = graphicsManager.CreateSprite(RESOURCES::PRISONER_R3_PATH);

		//left animation for player 2 
		playerImage2L1 = graphicsManager.CreateSprite(RESOURCES::PRISONER_L1_PATH);
		playerImage2L2 = graphicsManager.CreateSprite(RESOURCES::PRISONER_L2_PATH);
		playerImage2L3 = graphicsManager.CreateSprite(RESOURCES::PRISONER_L3_PATH);

		guardImage = graphicsManager.CreateSprite(RESOURCES::SECURITYGUARD_F1_PATH);
		securityCamImage = graphicsManager.CreateSprite(RESOURCES::CAMERA_PATH);
		exitImage = graphicsManager.CreateSprite(RESOURCES::VENDING_LEFT_PATH);
		computerSprite = graphicsManager.CreateSprite(RESOURCES::COMPUTER_PATH);
		doorSprite = graphicsManager.CreateSprite(RESOURCES::DOOR_PATH);
		boi = graphicsManager.CreateSprite(RESOURCES::PROTOTYPE_SPRITE_2_PATH);

		//indicator sprite
		indicator = graphicsManager.CreateSprite(RESOURCES::INDICATOR_PATH);
	}

	//Initialization of game objects, components and scripts.
	void StarBangBang::Level_Demo::Init()
	{

		PathFinder::PathFinderInit();
		PathFinder::ShowGrid(true);

		god = false;
		GRAPHICS::SetBackgroundColor(Black);

		//Load tilemap
		tilemap.SetCollidableTypes({ TileType::BRICK_BLACK });
		tilemap.Load(RESOURCES::LEVELS::LEVEL_TEST_PATH);

		tilemap.SetGrid(PathFinder::GetWorldGrid());
		//tilemap.SetVisible(false);

		//Movement controller
		movementController = objectManager.NewGameObject();
		MovementManager& moveMgr = objectManager.AddComponent<MovementManager>(movementController);


		//Client
		CaptainStealth::SpawnClient(objectManager, player2, player2Image);
		player2->transform.position = tilemap.GetPositionAtIndex(8, 3);


		//Player components and scripts
		CaptainStealth::SpawnPlayer(objectManager, player, playerImage);
		player->transform.position = tilemap.GetPositionAtIndex(6, 3);

		//character indicator
		indicatorObj = objectManager.NewGameObject();
		objectManager.AddComponent<ImageComponent>(indicatorObj, indicator);
		indicatorObj->transform.scale = {0.65f, 0.65f};
		
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

		//indicator update
		if (character == current_char::fei_ge)
		{
			indicatorObj->SetPos(player->GetPos());
			indicatorObj->transform.position.y += 30.0f;
		}
		else if (character == current_char::prisoner)
		{
			indicatorObj->SetPos(player2->GetPos());
			indicatorObj->transform.position.y += 30.0f;
		}


		//update animation for prisoner and client
		switch (character)
		{
		case current_char::fei_ge:

			switch (dir)
			{//fei ge's animation

			case direction::right:

				switch (animation_counter)
				{
				case 1:
					player->GetComponent<ImageComponent>()->SetSprite(playerImageR2);
					break;
				case 2:
					player->GetComponent<ImageComponent>()->SetSprite(playerImageR3);
					break;

				case 3:
					player->GetComponent<ImageComponent>()->SetSprite(playerImageR1);
					break;
				}

				break;

			case direction::left:

				switch (animation_counter)
				{
				case 1:
					player->GetComponent<ImageComponent>()->SetSprite(playerImageL2);
					break;
				case 2:
					player->GetComponent<ImageComponent>()->SetSprite(playerImageL3);
					break;
				case 3:
					player->GetComponent<ImageComponent>()->SetSprite(playerImageL1);
					break;
				}

				break;
			}

			break;

		case current_char::prisoner:
			switch (dir)
			{
				//prisoner's animation
			
			case direction::right:

				switch (animation_counter)
				{
				case 1:
					player2->GetComponent<ImageComponent>()->SetSprite(playerImage2R2);
					break;
				case 2:
					player2->GetComponent<ImageComponent>()->SetSprite(playerImage2R3);
					break;
				case 3:
					player2->GetComponent<ImageComponent>()->SetSprite(playerImage2R1);
					break;
				}

				break;

			case direction::left:

				switch (animation_counter)
				{
				case 1:
					player2->GetComponent<ImageComponent>()->SetSprite(playerImage2L2);
					break;
				case 2:
					player2->GetComponent<ImageComponent>()->SetSprite(playerImage2L3);
					break;

				case 3:
					player2->GetComponent<ImageComponent>()->SetSprite(playerImage2L1);
					break;
				}

				break;

			}
			break;
			
		}

		//ANIMATION ~~~

		//this is to switch characters
		if (AEInputCheckTriggered(AEVK_TAB))
		{
			if (character == current_char::fei_ge)
			{
				character = current_char::prisoner;
			}

			else if (character == current_char::prisoner)
			{
				character = current_char::fei_ge;
			}
		}

		if (!(AEInputCheckCurr(AEVK_W) || AEInputCheckCurr(AEVK_S) || AEInputCheckCurr(AEVK_A) || AEInputCheckCurr(AEVK_D)))
		{
			animation_counter = 3;
		}

		if (AEInputCheckCurr(AEVK_D))
		{
			dir = direction::right;
			app_time = app_time + g_dt;
		}
		else if (AEInputCheckCurr(AEVK_A))
		{
			dir = direction::left;
			app_time = app_time + g_dt;
		}

		else if (AEInputCheckCurr(AEVK_W) || AEInputCheckCurr(AEVK_S))
		{
			app_time = app_time + g_dt;
		}

		if (app_time >= 0.1f)
		{
			animation_counter++;
			app_time = 0.0f;
			if (animation_counter > 2) animation_counter = 0;
		}


		if (AEInputCheckTriggered(VK_SPACE))
		{
			MessageBus::Notify({ EventId::PRINT_TEXT, std::string("Find the Exit!") });
		}

		if (AEInputCheckTriggered(AEVK_ESCAPE))
		{
			gameStateManager.SetNextGameState(MAIN_MENU);
		}

		PlayerScript* playerScript = player->GetComponent<PlayerScript>();
		if (AEInputCheckTriggered(AEVK_G))
		{
			playerScript->Debug_Reset();
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
		Color dark = { 0, 0, 0, 0.5f };
		Color light = { 1.0f, 1.0f, 1.0f, 0.5f };
		GRAPHICS::DrawOverlay(graphicsManager.GetMesh(), { 20, 20 }, { 0, 0 }, dark, AE_GFX_BM_BLEND);
	}

	void StarBangBang::Level_Demo::Free()
	{
		PathFinder::Free();
		Scene::Free();
		

	}

	void StarBangBang::Level_Demo::Unload()
	{
		tilemap.Unload();
		Scene::Unload();
	}

}