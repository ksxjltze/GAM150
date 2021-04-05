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
#include "Disappear.h"

#include "CaptainStealth.h"
#include "DebugText.h"

#include "Click.h"
#include "UIComponent.h"
#include "SoundEvent.h"

#include "Settings.h"

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
	Sprite settingsBtnSprite;
	Sprite continueBtnSprite;

	struct Pause
	{
		GameObject* exitBtn{ nullptr };
		GameObject* settingsBtn{ nullptr };
		GameObject* continueBtn{ nullptr };
		GameObject* settingsObj{ nullptr };

		std::queue<GameObject*> windowQueue;

		bool active{ false };

		void DisplaySettings()
		{
			if (windowQueue.empty())
			{
				exitBtn->active = false;
				settingsBtn->active = false;
				continueBtn->active = false;
				settingsObj->GetComponent<SettingsMenu>()->SetStatus(true);
				windowQueue.push(settingsObj);
			}
		}

		bool CloseWindow()
		{
			if (!windowQueue.empty())
			{
				exitBtn->active = true;
				settingsBtn->active = true;
				continueBtn->active = true;
				windowQueue.front()->SetActive(false);
				windowQueue.pop();
				return false;
			}
			return true;
		}

		void Update() 
		{
			settingsObj->GetComponent<SettingsMenu>()->ForceUpdate();
			for (auto& component : exitBtn->GetComponents())
			{
				component->Update();
			}

			for (auto& component : continueBtn->GetComponents())
			{
				component->Update();
			}

			for (auto& component : settingsBtn->GetComponents())
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

		//interactable objs
		vendingMachineSprite = graphicsManager.CreateSprite(RESOURCES::VENDING_LEFT_PATH);
		computerSprite = graphicsManager.CreateSprite(RESOURCES::COMPUTER_PATH);
		doorSprite = graphicsManager.CreateSprite(RESOURCES::DOOR_PATH);
		keySprite = graphicsManager.CreateSprite(RESOURCES::KEY_PATH);
		ventOpenSprite = graphicsManager.CreateSprite(RESOURCES::VENT_OPEN_PATH);
		ventCloseSprite = graphicsManager.CreateSprite(RESOURCES::VENT_CLOSE_PATH);

		//indicator sprite
		indicator = graphicsManager.CreateSprite(RESOURCES::INDICATOR_PATH);
		boiSprite = graphicsManager.CreateSprite(RESOURCES::SPRITE_PLAYER_PATH);

		exitBtnSprite = graphicsManager.CreateSprite(RESOURCES::EXIT1_BUTTON_PATH);
		continueBtnSprite = graphicsManager.CreateSprite(RESOURCES::PLAY1_BUTTON_PATH);
		settingsBtnSprite = graphicsManager.CreateSprite(RESOURCES::SETTING1_BUTTON_PATH);
	}

	//Initialization of game objects, components and scripts.
	void StarBangBang::Level_Demo::Init()
	{
		paused = false;
		PathFinder::PathFinderInit();
		PathFinder::ShowGrid(false);

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

		// Create distractions
		int roomNum = 1;
		CreateDistraction(roomNum, 8, 12, vendingMachineSprite);

		roomNum = 2;
		CreateDistraction(roomNum, 30, 6, vendingMachineSprite);
		CreateDistraction(roomNum, 40, 10, computerSprite);

		roomNum = 3;
		CreateDistraction(roomNum, 41, 43, computerSprite);
		CreateDistraction(roomNum, 39, 37, vendingMachineSprite);

		roomNum = 4;
		CreateDistraction(roomNum, 15, 42, computerSprite);
		CreateDistraction(roomNum, 5, 21, computerSprite);
		CreateDistraction(roomNum, 16, 27, vendingMachineSprite);
		CreateDistraction(roomNum, 5, 47, vendingMachineSprite);

		CreateVent(11, 12, ventOpenSprite, ventCloseSprite);

		//Notification Text
		objectManager.AddComponent<DebugText>(objectManager.NewGameObject(), fontId);

		//Floating text
		MessageBus::Notify({ EventId::PRINT_TEXT, std::string("Find the Vending Machine!") });
		MessageBus::Notify({ EventId::PLAY_SOUND, SoundEvent("Test") });

		character = current_char::fei_ge;

		pauseMenu.settingsObj = objectManager.NewGameObject();
		objectManager.AddComponent<SettingsMenu>(pauseMenu.settingsObj, graphicsManager).Init();
	}

	void StarBangBang::Level_Demo::Update()
	{
		if (IsIconic(AESysGetWindowHandle()))
			TogglePause();

		CameraComponent* camera = player->GetComponent<CameraComponent>();
		if (!GRAPHICS::IsFullscreen())
		{
			camera->scale = GRAPHICS::DEFAULT_ZOOM / 1.5f;
		}
		else
		{
			camera->scale = GRAPHICS::DEFAULT_ZOOM;
		}

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

		if (!(AEInputCheckCurr(KEYBIND::MOVEMENT_UP) || AEInputCheckCurr(KEYBIND::MOVEMENT_DOWN)		|| 
			AEInputCheckCurr(KEYBIND::MOVEMENT_LEFT) || AEInputCheckCurr(KEYBIND::MOVEMENT_RIGHT)		||
			AEInputCheckCurr(KEYBIND::MOVEMENT_UP_ALT) || AEInputCheckCurr(KEYBIND::MOVEMENT_DOWN_ALT)	||
			AEInputCheckCurr(KEYBIND::MOVEMENT_LEFT_ALT) || AEInputCheckCurr(KEYBIND::MOVEMENT_RIGHT_ALT)))
		{
			animation_counter = 3;
		}

		if (AEInputCheckCurr(KEYBIND::MOVEMENT_RIGHT) || AEInputCheckCurr(KEYBIND::MOVEMENT_RIGHT_ALT))
		{
			dir = direction::right;
			app_time = app_time + g_dt;
		}
		else if (AEInputCheckCurr(KEYBIND::MOVEMENT_LEFT) || AEInputCheckCurr(KEYBIND::MOVEMENT_LEFT_ALT))
		{
			dir = direction::left;
			app_time = app_time + g_dt;
		}

		else if (AEInputCheckCurr(KEYBIND::MOVEMENT_UP)	|| 
		AEInputCheckCurr(KEYBIND::MOVEMENT_DOWN)		||
			AEInputCheckCurr(KEYBIND::MOVEMENT_UP_ALT)	||
				AEInputCheckCurr(KEYBIND::MOVEMENT_DOWN_ALT))
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
		//if (AEInputCheckTriggered(AEVK_G))
		//{
		//	playerScript->Debug_Reset();
		//	if (!god)
		//	{
		//		god = true;
		//		MessageBus::Notify({ EventId::PRINT_TEXT, std::string("God Mode Enabled!") });
		//	}
		//	else
		//	{
		//		god = false;
		//		MessageBus::Notify({ EventId::PRINT_TEXT, std::string("God Mode Disabled!") });
		//	}
		//}

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
		pauseMenu.settingsBtn->GetComponent<UIComponent>()->Draw();
		pauseMenu.settingsObj->GetComponent<SettingsMenu>()->Draw();
	}

	void Level_Demo::TogglePause()
	{
		if (pauseMenu.CloseWindow())
		{
			paused = !paused;
			pauseMenu.exitBtn->active = paused;
			pauseMenu.settingsBtn->active = paused;
			pauseMenu.continueBtn->active = paused;
			pauseMenu.settingsObj->active = false;
		}
	}

	void Level_Demo::ToggleSettings()
	{
		pauseMenu.DisplaySettings();
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
		objectManager.AddComponent<UIComponent>(pauseMenu.exitBtn, exitBtnSprite, graphicsManager).active = false;
		pauseMenu.exitBtn->transform.position.y = -100;
		pauseMenu.exitBtn->transform.scale = { 3, 3 };
		pauseMenu.exitBtn->active = false;

		pauseMenu.continueBtn = objectManager.NewGameObject();
		objectManager.AddComponent<Click<Level_Demo>>(pauseMenu.continueBtn, true).setCallback(*this, &Level_Demo::TogglePause);
		objectManager.AddComponent<UIComponent>(pauseMenu.continueBtn, continueBtnSprite, graphicsManager).active = false;
		pauseMenu.continueBtn->transform.position.y = 100;
		pauseMenu.continueBtn->transform.scale = { 3, 3 };
		pauseMenu.continueBtn->active = false;

		pauseMenu.settingsBtn = objectManager.NewGameObject();
		objectManager.AddComponent<Click<Level_Demo>>(pauseMenu.settingsBtn, true).setCallback(*this, &Level_Demo::ToggleSettings);
		objectManager.AddComponent<UIComponent>(pauseMenu.settingsBtn, settingsBtnSprite, graphicsManager).active = false;
		pauseMenu.settingsBtn->transform.position.y = 0;
		pauseMenu.settingsBtn->transform.scale = { 3, 3 };
		pauseMenu.settingsBtn->active = false;
	}

	void Level_Demo::CreateDistraction(unsigned int roomNum, int tileX, int tileY, const Sprite& sprite)
	{
		GameObject* distraction = objectManager.NewGameObject();
		distraction->transform.position = tilemap.GetPositionAtIndex(tileX, tileY);
		objectManager.AddComponent<Distractor>(distraction).SetRoomNum(roomNum);
		objectManager.AddImage(distraction, sprite);
		objectManager.AddCollider(distraction, true).isTrigger = true;
	}

	void Level_Demo::CreateVent(int tileX, int tileY, Sprite& spriteOpen,  Sprite& spriteClose)
	{
		GameObject* vent = objectManager.NewGameObject();
		vent->transform.position = tilemap.GetPositionAtIndex(tileX, tileY);
		objectManager.AddComponent<Disappear>(vent, spriteOpen, spriteClose);
		objectManager.AddImage(vent, spriteOpen);
		objectManager.AddCollider(vent, true).isTrigger = true;
	}
}