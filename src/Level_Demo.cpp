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
#include "VisionCone.h"
#include "SoundEvent.h"

#include "Settings.h"
#include "PlayerAnimation.h"

static bool god = false;
static float app_time = 0.0f;
static int animation_counter = 0;

static StarBangBang::AnimationSprites animSprites;

namespace StarBangBang
{
	Sprite computerSprite;
	Sprite doorSprite;
	Sprite keySprite;
	Sprite boiSprite;
	Sprite exitBtnSprite;
	Sprite settingsBtnSprite;
	Sprite continueBtnSprite;
	Sprite stealth_icon;

	std::map<GameObject*, current_char> charMap;
	
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
			SettingsMenu* settings = settingsObj->GetComponent<SettingsMenu>();
			settings->ForceUpdate();

			if (windowQueue.empty())
			{
				settings->SetStatus(false);
			}
			else if (!windowQueue.front()->active)
			{
				CloseWindow();
			}

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
		dir = direction::idle;
		character = current_char::fei_ge;
	}

	void StarBangBang::Level_Demo::Load()
	{
		//forward player 1
		playerImage = graphicsManager.CreateSprite(RESOURCES::CAPTAINSTEALTH_F1_PATH);

		//player 2
		player2Image = graphicsManager.CreateSprite(RESOURCES::PRISONER_F1_PATH);

		animSprites.Load(graphicsManager);
		GuardAnim::Load(graphicsManager);

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


		stealth_icon = graphicsManager.CreateSprite(RESOURCES::EYE_SPRITE_PATH);
	}

	//Initialization of game objects, components and scripts.
	void StarBangBang::Level_Demo::Init()
	{
		paused = false;
		ShowCursor(FALSE);
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
		moveMgr.gameObject->name = "MovementManager";


		//Client
		CaptainStealth::SpawnClient(objectManager, player2, player2Image);
		player2->transform.position = tilemap.GetPositionAtIndex(8, 3);


		//Player components and scripts
		CaptainStealth::SpawnPlayer(objectManager, player, playerImage);
		player->transform.position = tilemap.GetPositionAtIndex(6, 3);

		charMap.insert({ player, current_char::fei_ge});
		charMap.insert({ player2, current_char::prisoner});
		

		//UI
		GameObject* UI = objectManager.NewGameObject();
		UIComponent& UICom = objectManager.AddComponent<UIComponent>(UI, stealth_icon,graphicsManager);
		UICom.rescale = false;
		UICom.gameObject->SetLayer(LAYER::UI);
		UICom.SetColor(Color{1.0f,1.0f,1.0f,0.7f});
		Text& uiText = objectManager.AddComponent<Text>(objectManager.NewGameObject(), "Q", fontId, White, 1.0f, false);
		uiText.gameObject->transform.position = { 0.05f, 0.28f };
		uiText.SetOffset({ -1.0f, -1.0f });
		UI->transform.position = {-AEGetWindowWidth()/2 + 0.05f * AEGetWindowWidth(), -AEGetWindowHeight()/2 + 0.1f * AEGetWindowHeight() };
		uiText.gameObject->name = "Stealth_Txt";
		UI->name = "Stealth_UI";


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

		//room1
		CreateVent(11, 12);
		CreateVent(18, 7);

		//room 2
		CreateVent(30, 10);
		//CreateVent(30, 16);
		//CreateVent(35, 13);
		CreateVent(45, 13);
		CreateVent(42, 4);

		//room 3
		CreateVent(21, 26);
		CreateVent(40, 24);
		CreateVent(45, 39);
		CreateVent(35, 36);
		CreateVent(26, 43);
		//CreateVent(41, 43);

		//room 4
		CreateVent(15, 41);
		CreateVent(15, 33);
		CreateVent(8, 20);
		//CreateVent(7, 37);
		CreateVent(7, 45);
		//CreateVent(6, 26);

		//Notification Text
		objectManager.AddComponent<DebugText>(objectManager.NewGameObject(), fontId);

		//Floating text
		MessageBus::Notify({ EventId::PRINT_TEXT, std::string("Find the Vending Machine!") });
		MessageBus::Notify({ EventId::PLAY_SOUND, SoundEvent("Test") });

		character = current_char::fei_ge;

		//TEST
		//player->transform.position = tilemap.GetPositionAtIndex(5, 34);
		//player2->transform.position = tilemap.GetPositionAtIndex(6, 34);

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

		GameObject* activeCharacter = objectManager.Find("MovementManager")->GetComponent<MovementManager>()->GetActiveController();
		character = charMap.at(activeCharacter);

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
		
		PlayerAnimator::PlayerAnimation(dir, character, player, player2, animSprites, animation_counter);

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


		//if (AEInputCheckTriggered(VK_SPACE))
		//{
		//	MessageBus::Notify({ EventId::PRINT_TEXT, std::string("Find the Exit!") });
		//}

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
				ShowCursor(TRUE);
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
		GRAPHICS::DrawOverlay(graphicsManager.GetMesh(), nullptr, { 40, 40 }, { 0, 0 }, { 0, 0, 0, 0.7f });
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
			ShowCursor(paused);
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
		pauseMenu.exitBtn->transform.scale = { 3, 1.5f };
		pauseMenu.exitBtn->active = false;

		pauseMenu.continueBtn = objectManager.NewGameObject();
		objectManager.AddComponent<Click<Level_Demo>>(pauseMenu.continueBtn, true).setCallback(*this, &Level_Demo::TogglePause);
		objectManager.AddComponent<UIComponent>(pauseMenu.continueBtn, continueBtnSprite, graphicsManager).active = false;
		pauseMenu.continueBtn->transform.position.y = 100;
		pauseMenu.continueBtn->transform.scale = { 3, 1.5f };
		pauseMenu.continueBtn->active = false;

		pauseMenu.settingsBtn = objectManager.NewGameObject();
		objectManager.AddComponent<Click<Level_Demo>>(pauseMenu.settingsBtn, true).setCallback(*this, &Level_Demo::ToggleSettings);
		objectManager.AddComponent<UIComponent>(pauseMenu.settingsBtn, settingsBtnSprite, graphicsManager).active = false;
		pauseMenu.settingsBtn->transform.position.y = 0;
		pauseMenu.settingsBtn->transform.scale = { 3, 1.5f };
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

	void Level_Demo::CreateVent(int tileX, int tileY)
	{
		GameObject* vent = objectManager.NewGameObject();
		vent->transform.position = tilemap.GetPositionAtIndex(tileX, tileY);
		objectManager.AddComponent<Disappear>(vent, ventOpenSprite, ventCloseSprite);
		objectManager.AddImage(vent, ventOpenSprite);
		objectManager.AddCollider(vent, true).isTrigger = true;
	}
}