#include "Main_Menu.h"
#include "constants.h"
#include "Click.h"


static const float x_scale = 5.0f;
static const float y_scale = 5.0f;
static const float WinWidth = (float)AEGetWindowWidth();
static const float WinHeight = (float)AEGetWindowHeight();

namespace StarBangBang
{
	StarBangBang::Main_Menu::Main_Menu(int id, GameStateManager& manager) : Scene(id, manager), tilemap{ objectManager, graphicsManager }
	{
		logo_obj = nullptr;
		playbutton_obj = nullptr;
		settingsbutton_obj = nullptr;
		creditsbutton_obj = nullptr;
		exitbutton_obj = nullptr;
	}

	void StarBangBang::Main_Menu::Load()
	{
		tilemap.Load(RESOURCES::LEVEL_MAIN_MENU_TEST_PATH);
		//load button images
		logo = graphicsManager.CreateSprite(RESOURCES::LOGO_PATH,256,64);

		playbutton1 = graphicsManager.CreateSprite(RESOURCES::PLAY1_BUTTON_PATH);
		settingsbutton1 = graphicsManager.CreateSprite(RESOURCES::SETTING1_BUTTON_PATH);
		creditsbutton1 = graphicsManager.CreateSprite(RESOURCES::CREDIT1_BUTTON_PATH);
		exitbutton1 = graphicsManager.CreateSprite(RESOURCES::EXIT1_BUTTON_PATH);

		playbutton2 = graphicsManager.CreateSprite(RESOURCES::PLAY2_BUTTON_PATH);
		settingsbutton2 = graphicsManager.CreateSprite(RESOURCES::SETTING2_BUTTON_PATH);
		creditsbutton2 = graphicsManager.CreateSprite(RESOURCES::CREDIT2_BUTTON_PATH);
		exitbutton2 = graphicsManager.CreateSprite(RESOURCES::EXIT2_BUTTON_PATH);
	}

	void StarBangBang::Main_Menu::Init()
	{
		//logo 
		logo_obj = objectManager.NewGameObject();
		objectManager.AddImage(logo_obj, logo);
		logo_obj->transform.position = { 0, (float)AEGetWindowHeight() / 3 };
		logo_obj->transform.scale = { 1.5,1.5};


		//start game button
		playbutton_obj = objectManager.NewGameObject();
		objectManager.AddImage(playbutton_obj, playbutton1);
		playbutton_obj->transform.position = { (float)AEGetWindowWidth() / -8, (float)AEGetWindowHeight() / 8 };
		playbutton_obj->transform.scale = { 1.5, 1.5 };

		auto d = []() {printf("MAIN MENU: TEST\n"); };
		objectManager.AddComponent<Click<Main_Menu>>(playbutton_obj).setCallback(*this, &Main_Menu::LoadLevelTest);
		

		//settings button
		settingsbutton_obj = objectManager.NewGameObject();
		objectManager.AddImage(settingsbutton_obj, settingsbutton1);
		settingsbutton_obj->transform.position = { (float)AEGetWindowWidth() / 8, (float)AEGetWindowHeight() / 8 };
		settingsbutton_obj->transform.scale = { 1.5, 1.5 };

		//credits button
		creditsbutton_obj = objectManager.NewGameObject();
		objectManager.AddImage(creditsbutton_obj, creditsbutton1);
		creditsbutton_obj->transform.position = { (float)AEGetWindowWidth() / -8, (float)AEGetWindowHeight() / -8 };
		creditsbutton_obj->transform.scale = { 1.5, 1.5 };

		//exit game button
		exitbutton_obj = objectManager.NewGameObject();
		objectManager.AddImage(exitbutton_obj, exitbutton1);
		exitbutton_obj->transform.position = { (float)AEGetWindowWidth() / 8, (float)AEGetWindowHeight() / -8, };
		exitbutton_obj->transform.scale = { 1.5,1.5 };
	}

	void StarBangBang::Main_Menu::Update()
	{
		Scene::Update();
		if (AEInputCheckTriggered(AEVK_SPACE))
		{
			gameStateManager.SetNextGameState(SceneID::SAMPLE);
		}
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
	}

	void Main_Menu::LoadLevelTest()
	{
		gameStateManager.SetNextGameState();
	}

}




