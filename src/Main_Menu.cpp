#include "Main_Menu.h"
#include "constants.h"
#include "Click.h"
#include "CollisionEvent.h"
#include "Settings.h"
#include "MusicEvent.h"
#include "ConfirmationMenu.h"
#include "globals.h"

static const float x_scale = 5.0f;
static const float y_scale = 5.0f;
static const float WinWidth = (float)AEGetWindowWidth();
static const float WinHeight = (float)AEGetWindowHeight();

namespace StarBangBang
{
	Sprite vending_machine_sprite;

	StarBangBang::Main_Menu::Main_Menu(int id, GameStateManager& manager) : Scene(id, manager), tilemap{ objectManager, graphicsManager }
	{
		tf = false;
		logo_obj = nullptr;
		playbutton_obj = nullptr;
		settingsbutton_obj = nullptr;
		creditsbutton_obj = nullptr;
		exitbutton_obj = nullptr;
		tutorialbutton_obj = nullptr;
	}

	void StarBangBang::Main_Menu::Load()
	{
		tilemap.Load(RESOURCES::LEVELS::LEVEL_MAIN_MENU_TEST_PATH);
		//load button images
		logo = graphicsManager.CreateSprite(RESOURCES::LOGO_PATH,256,64);

		playbutton1 = graphicsManager.CreateSprite(RESOURCES::PLAY1_BUTTON_PATH);
		settingsbutton1 = graphicsManager.CreateSprite(RESOURCES::SETTING1_BUTTON_PATH);
		creditsbutton1 = graphicsManager.CreateSprite(RESOURCES::CREDIT1_BUTTON_PATH);
		exitbutton1 = graphicsManager.CreateSprite(RESOURCES::EXIT1_BUTTON_PATH);
		tutorialButton1 = graphicsManager.CreateSprite(RESOURCES::TUTORIAL_BUTTON_PATH);

		playbutton2 = graphicsManager.CreateSprite(RESOURCES::PLAY2_BUTTON_PATH);
		settingsbutton2 = graphicsManager.CreateSprite(RESOURCES::SETTING2_BUTTON_PATH);
		creditsbutton2 = graphicsManager.CreateSprite(RESOURCES::CREDIT2_BUTTON_PATH);
		exitbutton2 = graphicsManager.CreateSprite(RESOURCES::EXIT2_BUTTON_PATH);

		vending_machine_sprite = graphicsManager.CreateSprite(RESOURCES::VENDING_LEFT_PATH);
	}

	void StarBangBang::Main_Menu::Init()
	{

		AEVec2 btnScale = { 3.0f, 1.6f};

		GRAPHICS::SetZoom(1.0f);
		GRAPHICS::SetBackgroundColor(Black);
		//logo 
		logo_obj = objectManager.NewGameObject();
		objectManager.AddImage(logo_obj, logo);
		logo_obj->transform.position = { 0, (float)AEGetWindowHeight() / 3 };
		logo_obj->transform.scale = { 1.5, 1.5};

		settingsObj = objectManager.NewGameObject();
		objectManager.AddComponent<SettingsMenu>(settingsObj, graphicsManager).Init();

		confirmationObj = objectManager.NewGameObject();
		ConfirmationMenu& confirm = objectManager.AddComponent<ConfirmationMenu>(confirmationObj, graphicsManager, gameStateManager);
		confirm.Init();
		confirm.SetText(std::string("Quit the game?"));

		//start game button
		playbutton_obj = objectManager.NewGameObject();
		//objectManager.AddImage(playbutton_obj, playbutton1);
		objectManager.AddComponent<ImageComponent>(playbutton_obj, playbutton1);
		playbutton_obj->transform.position = { (float)AEGetWindowWidth() / -8, (float)AEGetWindowHeight() / 8 };
		playbutton_obj->transform.scale = btnScale;
		objectManager.AddComponent<Click<Main_Menu>>(playbutton_obj).setCallback(*this, &Main_Menu::LoadLevel);
		
		//tutorial button
		tutorialbutton_obj = objectManager.NewGameObject();
		objectManager.AddImage(tutorialbutton_obj, tutorialButton1);
		tutorialbutton_obj->transform.position = { (float)AEGetWindowWidth() / 8, (float)AEGetWindowHeight() / 8 };
		tutorialbutton_obj->transform.scale = btnScale;
		objectManager.AddComponent<Click<Main_Menu>>(tutorialbutton_obj).setCallback(*this, &Main_Menu::LoadTutorial);

		//settings button
		settingsbutton_obj = objectManager.NewGameObject();
		objectManager.AddImage(settingsbutton_obj, settingsbutton1);
		settingsbutton_obj->transform.position = { (float)AEGetWindowWidth() / -8, (float)AEGetWindowHeight() / -8 };
		settingsbutton_obj->transform.scale = btnScale;
		objectManager.AddComponent<Click<Main_Menu>>(settingsbutton_obj).setCallback(*this, &Main_Menu::Settings);

		//credits button
		creditsbutton_obj = objectManager.NewGameObject();
		objectManager.AddImage(creditsbutton_obj, creditsbutton1);
		creditsbutton_obj->transform.position = { (float)AEGetWindowWidth() / 8, (float)AEGetWindowHeight() / -8 };
		creditsbutton_obj->transform.scale = btnScale;
		objectManager.AddComponent<Click<Main_Menu>>(creditsbutton_obj).setCallback(*this, &Main_Menu::Credits);

		//exit game button
		exitbutton_obj = objectManager.NewGameObject();
		objectManager.AddImage(exitbutton_obj, exitbutton1);
		exitbutton_obj->transform.position = { 0, -200 };
		exitbutton_obj->transform.scale = btnScale;

		objectManager.AddComponent<Click<Main_Menu>>(exitbutton_obj).setCallback(*this, &Main_Menu::ExitGame);

		MusicEvent bgm{ BGM::MENU };
		bgm.SendEvent();

		if (IsDebug())
		{
			GameObject* editorBtn = objectManager.NewGameObject();
			objectManager.AddImage(editorBtn, vending_machine_sprite);
			editorBtn->transform.position = { (float)AEGetWindowWidth() * 0.35f, (float)AEGetWindowHeight() / 8, };

			objectManager.AddComponent<Click<Main_Menu>>(editorBtn).setCallback(*this, &Main_Menu::LoadEditor);
		}

		frameSkip = true;
	}

	void StarBangBang::Main_Menu::Update()
	{
		//Hack to prevent input from being carried forward from previous scenes
		if (frameSkip)
		{
			frameSkip = false;
			return;
		}

		if (GRAPHICS::IsFullscreen())
			GRAPHICS::SetZoom(1.5f);
		else
			GRAPHICS::SetZoom(1.0f);

		if (windowOpen && !windowQueue.empty())
		{
			if (windowQueue.front()->active)
			{
				if (AEInputCheckTriggered(AEVK_ESCAPE))
				{
					windowQueue.front()->SetActive(false);
					windowQueue.pop();
				}

			}
			else
			{
				windowQueue.pop();
			}
		}
		else
			windowOpen = false;

		HideMenu();

		Scene::Update();

	}

	void StarBangBang::Main_Menu::Draw()
	{
		Scene::Draw();
	}

	void StarBangBang::Main_Menu::Free()
	{
		Scene::Free();
		tilemap.Unload();
	}

	void StarBangBang::Main_Menu::Unload()
	{
		Scene::Unload();
		MessageBus::Notify({ EventId::STOP_SOUND });
	}

	void Main_Menu::LoadEditor()
	{
		gameStateManager.SetNextGameState(SceneID::EDITOR);
	}

	void Main_Menu::LoadTutorial()
	{
		gameStateManager.SetNextGameState(SceneID::TUTORIAL);
	}

	void Main_Menu::LoadLevel()
	{
		gameStateManager.SetNextGameState(SceneID::GAME);
	}

	void Main_Menu::Credits()
	{
		gameStateManager.SetNextGameState(CREDITS);
	}

	void Main_Menu::ExitGame()
	{
		DisplayConfirmationMenu();
		//gameStateManager.ExitGame();
	}

	void Main_Menu::Settings()
	{
		windowOpen = true;
		settingsObj->SetActive(true);
		windowQueue.push(settingsObj);
	}

	void Main_Menu::DisplayConfirmationMenu()
	{
		windowOpen = true;
		confirmationObj->SetActive(true);
		windowQueue.push(confirmationObj);
	}

	void Main_Menu::HideMenu()
	{
		logo_obj->active = !windowOpen;
		playbutton_obj->active = !windowOpen;
		settingsbutton_obj->active = !windowOpen;
		creditsbutton_obj->active = !windowOpen;
		exitbutton_obj->active = !windowOpen;
		tutorialbutton_obj->active = !windowOpen;
		//editorBtn->active = !windowOpen;
	}
}




