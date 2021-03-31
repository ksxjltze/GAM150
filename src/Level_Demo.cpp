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

#include "Click.h"
#include "UIComponent.h"

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
	Sprite keySprite;
	Sprite boiSprite;
	Sprite exitBtnSprite;
	Sprite continueBtnSprite;

	struct Pause
	{
		GameObject* exitBtn{ nullptr };
		GameObject* continueBtn{ nullptr };
		void Update() 
		{
			for (auto& component : exitBtn->GetComponents())
			{
				component->Update();
			}

			for (auto& component : continueBtn->GetComponents())
			{
				component->Update();
			}
		}
	}pauseMenu;

	StarBangBang::BoxCollider* playerCol;
	StarBangBang::BoxCollider* clientCol;

	StarBangBang::Level_Demo::Level_Demo(int id, GameStateManager& manager) : Scene(id, manager), tilemap{ objectManager, graphicsManager }
	{
		player = nullptr;
		player2 = nullptr;
		movementController = nullptr;
		guardManager = nullptr;
		indicatorObj = nullptr;
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
		vendingMachineSprite = graphicsManager.CreateSprite(RESOURCES::VENDING_LEFT_PATH);
		computerSprite = graphicsManager.CreateSprite(RESOURCES::COMPUTER_PATH);
		doorSprite = graphicsManager.CreateSprite(RESOURCES::DOOR_PATH);
		keySprite = graphicsManager.CreateSprite(RESOURCES::KEY_PATH);

		//indicator sprite
		indicator = graphicsManager.CreateSprite(RESOURCES::INDICATOR_PATH);
		boiSprite = graphicsManager.CreateSprite(RESOURCES::SPRITE_PLAYER_PATH);

		exitBtnSprite = graphicsManager.CreateSprite(RESOURCES::EXIT1_BUTTON_PATH);
		continueBtnSprite = graphicsManager.CreateSprite(RESOURCES::PLAY1_BUTTON_PATH);
	}

	//Initialization of game objects, components and scripts.
	void StarBangBang::Level_Demo::Init()
	{
		paused = false;
		PathFinder::PathFinderInit();
		PathFinder::ShowGrid(true);

		god = false;
		GRAPHICS::SetBackgroundColor(Black);

		//Load tilemap
		tilemap.SetCollidableTypes({ TileType::BRICK_BLACK });
		tilemap.Load(RESOURCES::LEVELS::LEVEL_TEST_PATH);

		tilemap.SetGrid(PathFinder::GetWorldGrid());
		CollisionManager::SetDebugVisible(false);
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
		//srand(static_cast<unsigned int>(time(NULL)));
		//for (int i = 0; i < CONSTANTS::COMPUTER_COUNT; ++i)
		//{
		//	Grid& grid = PathFinder::GetWorldGrid();
		//	A_Node n = grid.GetRandomFreeNode();
		//	CaptainStealth::SpawnComputer(objectManager, computerSprite, n.nodePos);
		//}

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
		exit->transform.position = tilemap.GetPositionAtIndex(1, 34);
		exit->name = "EXIT";
		objectManager.AddImage(exit, boiSprite);
		objectManager.AddCollider(exit, true).isTrigger = true;

		SpawnDoors();

		InitPause();

		//room 1 distractor
		GameObject* distract2 = objectManager.NewGameObject();
		//temp
		distract2->transform.position = tilemap.GetPositionAtIndex(8, 12);
		objectManager.AddComponent<Distractor>(distract2).SetRoomNum(1);
		objectManager.AddImage(distract2, vendingMachineSprite);
		objectManager.AddCollider(distract2, true).isTrigger = true;

		//room 2 distractor
		GameObject* distract10 = objectManager.NewGameObject();
		//temp
		distract10->transform.position = tilemap.GetPositionAtIndex(30, 6);
		objectManager.AddComponent<Distractor>(distract10).SetRoomNum(2);
		objectManager.AddImage(distract10, vendingMachineSprite);
		objectManager.AddCollider(distract10, true).isTrigger = true;

		GameObject* distract11 = objectManager.NewGameObject();
		//temp
		distract11->transform.position = tilemap.GetPositionAtIndex(40, 10);
		objectManager.AddComponent<Distractor>(distract11).SetRoomNum(2);
		objectManager.AddImage(distract11, computerSprite);
		objectManager.AddCollider(distract11, true).isTrigger = true;

		//room 3 distractor
		GameObject* distract3 = objectManager.NewGameObject();
		//temp
		distract3->transform.position = tilemap.GetPositionAtIndex(31, 7);
		objectManager.AddComponent<Distractor>(distract3).SetRoomNum(3);
		objectManager.AddImage(distract3, computerSprite);
		objectManager.AddCollider(distract3, true).isTrigger = true;
		
		GameObject* distract8 = objectManager.NewGameObject();
		//temp
		distract8->transform.position = tilemap.GetPositionAtIndex(41, 43);
		objectManager.AddComponent<Distractor>(distract8).SetRoomNum(3);
		objectManager.AddImage(distract8, computerSprite);
		objectManager.AddCollider(distract8, true).isTrigger = true;

		GameObject* distract9 = objectManager.NewGameObject();
		//temp
		distract9->transform.position = tilemap.GetPositionAtIndex(39, 37);
		objectManager.AddComponent<Distractor>(distract9).SetRoomNum(3);
		objectManager.AddImage(distract9, vendingMachineSprite);
		objectManager.AddCollider(distract9, true).isTrigger = true;



		//room 4 distractor
		GameObject* distract4 = objectManager.NewGameObject();
		//temp
		distract3->transform.position = tilemap.GetPositionAtIndex(15, 42);
		objectManager.AddComponent<Distractor>(distract4).SetRoomNum(4);
		objectManager.AddImage(distract4, computerSprite);
		objectManager.AddCollider(distract4, true).isTrigger = true;

		GameObject* distract5 = objectManager.NewGameObject();
		//temp
		distract5->transform.position = tilemap.GetPositionAtIndex(5, 21);
		objectManager.AddComponent<Distractor>(distract5).SetRoomNum(4);
		objectManager.AddImage(distract5, computerSprite);
		objectManager.AddCollider(distract5, true).isTrigger = true;

		GameObject* distract6 = objectManager.NewGameObject();
		//temp
		distract6->transform.position = tilemap.GetPositionAtIndex(16, 27);
		objectManager.AddComponent<Distractor>(distract6).SetRoomNum(4);
		objectManager.AddImage(distract6, vendingMachineSprite);
		objectManager.AddCollider(distract6, true).isTrigger = true;

		GameObject* distract7 = objectManager.NewGameObject();
		//temp
		distract7->transform.position = tilemap.GetPositionAtIndex(5, 47);
		objectManager.AddComponent<Distractor>(distract7).SetRoomNum(4);
		objectManager.AddImage(distract7, vendingMachineSprite);
		objectManager.AddCollider(distract7, true).isTrigger = true;

		//Notification Text
		objectManager.AddComponent<DebugText>(objectManager.NewGameObject(), fontId);

		//Floating text
		MessageBus::Notify({ EventId::PRINT_TEXT, std::string("Find the Vending Machine!") });
		MessageBus::Notify({ EventId::PLAY_SOUND, "Test"});

		character = current_char::fei_ge;
	}

	void StarBangBang::Level_Demo::Update()
	{
		if (AEInputCheckTriggered(AEVK_ESCAPE))
		{
			TogglePause();
			//gameStateManager.SetNextGameState(MAIN_MENU);
		}

		if (paused)
		{
			if (AEInputCheckTriggered(AEVK_RETURN))
			{
				TogglePause();
				return;
			}
			pauseMenu.Update();
			return;
		}

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

		if (!(AEInputCheckCurr(KEYBIND::MOVEMENT_UP) || AEInputCheckCurr(KEYBIND::MOVEMENT_DOWN) || AEInputCheckCurr(KEYBIND::MOVEMENT_LEFT) || AEInputCheckCurr(KEYBIND::MOVEMENT_RIGHT)))
		{
			animation_counter = 3;
		}

		if (AEInputCheckCurr(KEYBIND::MOVEMENT_RIGHT))
		{
			dir = direction::right;
			app_time = app_time + g_dt;
		}
		else if (AEInputCheckCurr(KEYBIND::MOVEMENT_LEFT))
		{
			dir = direction::left;
			app_time = app_time + g_dt;
		}

		else if (AEInputCheckCurr(KEYBIND::MOVEMENT_UP) || AEInputCheckCurr(KEYBIND::MOVEMENT_DOWN))
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

		// draw occupied pathfinding nodes for debugging
		PathFinder::GridDraw();

		if (paused)
			DisplayPauseMenu();

		//Color dark = { 0, 0, 0, 0.5f };
		//Color light = { 1.0f, 1.0f, 1.0f, 0.5f };
		//GRAPHICS::DrawOverlay(graphicsManager.GetMesh(), { 20, 20 }, { 0, 0 }, dark, AE_GFX_BM_BLEND);
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

	void Level_Demo::Exit()
	{
		gameStateManager.SetNextGameState(MAIN_MENU);
	}

	void Level_Demo::DisplayPauseMenu()
	{
		GRAPHICS::DrawOverlay(graphicsManager.GetMesh(), nullptr, { 20, 20 }, { 0, 0 }, { 0, 0, 0, 0.7f });
		pauseMenu.exitBtn->GetComponent<UIComponent>()->Draw();
		pauseMenu.continueBtn->GetComponent<UIComponent>()->Draw();
	}

	void Level_Demo::TogglePause()
	{
		paused = !paused;

		pauseMenu.continueBtn->active = paused;
		pauseMenu.exitBtn->active = paused;
	}

	void Level_Demo::SpawnDoors()
	{
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Door
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		//First room door


		Door* door = CaptainStealth::SpawnDoor(objectManager, doorSprite, tilemap.GetPositionAtIndex(20, 9));
		Door* door2 = CaptainStealth::SpawnDoor(objectManager, doorSprite, tilemap.GetPositionAtIndex(20, 8));
		Door* door3 = CaptainStealth::SpawnDoor(objectManager, doorSprite, tilemap.GetPositionAtIndex(20, 7));

		CaptainStealth::SpawnKey(objectManager, door, keySprite, tilemap.GetPositionAtIndex(14, 12));
		CaptainStealth::SpawnKey(objectManager, door, keySprite, tilemap.GetPositionAtIndex(3, 2));
		door->Link({ door2, door3 });

		//Second room door
		door = CaptainStealth::SpawnDoor(objectManager, doorSprite, tilemap.GetPositionAtIndex(35, 20));
		door2 = CaptainStealth::SpawnDoor(objectManager, doorSprite, tilemap.GetPositionAtIndex(36, 20));
		door3 = CaptainStealth::SpawnDoor(objectManager, doorSprite, tilemap.GetPositionAtIndex(37, 20));

		CaptainStealth::SpawnKey(objectManager, door, keySprite, tilemap.GetPositionAtIndex(45, 6));
		CaptainStealth::SpawnKey(objectManager, door, keySprite, tilemap.GetPositionAtIndex(48, 18));
		door->Link({ door2, door3 });

		//Third room door
		door = CaptainStealth::SpawnDoor(objectManager, doorSprite, tilemap.GetPositionAtIndex(19, 36));
		door2 = CaptainStealth::SpawnDoor(objectManager, doorSprite, tilemap.GetPositionAtIndex(19, 35));
		door3 = CaptainStealth::SpawnDoor(objectManager, doorSprite, tilemap.GetPositionAtIndex(19, 34));

		CaptainStealth::SpawnKey(objectManager, door, keySprite, tilemap.GetPositionAtIndex(46, 44));
		CaptainStealth::SpawnKey(objectManager, door, keySprite, tilemap.GetPositionAtIndex(21, 44));
		door->Link({ door2, door3 });

		//Fourth room door
		door = CaptainStealth::SpawnDoor(objectManager, doorSprite, tilemap.GetPositionAtIndex(3, 35));
		door2 = CaptainStealth::SpawnDoor(objectManager, doorSprite, tilemap.GetPositionAtIndex(3, 34));
		door3 = CaptainStealth::SpawnDoor(objectManager, doorSprite, tilemap.GetPositionAtIndex(3, 33));

		CaptainStealth::SpawnKey(objectManager, door, keySprite, tilemap.GetPositionAtIndex(15, 19));
		CaptainStealth::SpawnKey(objectManager, door, keySprite, tilemap.GetPositionAtIndex(16, 47));
		door->Link({ door2, door3 });
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
	}

	void Level_Demo::InitPause()
	{
		///Pause
		pauseMenu.exitBtn = objectManager.NewGameObject();
		objectManager.AddComponent<Click<Level_Demo>>(pauseMenu.exitBtn, true).setCallback(*this, &Level_Demo::Exit);
		objectManager.AddComponent<UIComponent>(pauseMenu.exitBtn, exitBtnSprite);
		pauseMenu.exitBtn->transform.position.y = -100;
		pauseMenu.exitBtn->transform.scale = { 3, 3 };
		pauseMenu.exitBtn->active = false;

		pauseMenu.continueBtn = objectManager.NewGameObject();
		objectManager.AddComponent<Click<Level_Demo>>(pauseMenu.continueBtn, true).setCallback(*this, &Level_Demo::TogglePause);
		objectManager.AddComponent<UIComponent>(pauseMenu.continueBtn, continueBtnSprite);
		pauseMenu.continueBtn->transform.position.y = 100;
		pauseMenu.continueBtn->transform.scale = { 3, 3 };
		pauseMenu.continueBtn->active = false;
	}

}