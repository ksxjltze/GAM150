#include "Main_Menu.h"
#include "constants.h"


static const float x_scale = 5.0f;
static const float y_scale = 5.0f;
static const float WinWidth = (float)AEGetWindowWidth();
static const float WinHeight = (float)AEGetWindowHeight();


StarBangBang::Main_Menu::Main_Menu(int id, GameStateManager& manager) : Scene(id, manager)
{

}

void StarBangBang::Main_Menu::Load()
{
	//load button images
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
	//start game button
	playbutton_obj = objectManager.NewGameObject();
	objectManager.AddImage(playbutton_obj, playbutton1);
	playbutton_obj->transform.position = { (float)AEGetWindowWidth()/-8, (float)AEGetWindowHeight() / 8 };

	//settings button
	settingsbutton_obj = objectManager.NewGameObject();
	objectManager.AddImage(settingsbutton_obj, settingsbutton1);
	settingsbutton_obj->transform.position = { (float)AEGetWindowWidth() / 8, (float)AEGetWindowHeight() / 8 };

	//credits button
	creditsbutton_obj = objectManager.NewGameObject();
	objectManager.AddImage(creditsbutton_obj, creditsbutton1);
	creditsbutton_obj->transform.position = { (float)AEGetWindowWidth() / -8, (float)AEGetWindowHeight() / -8 };

	//exit game button
	exitbutton_obj = objectManager.NewGameObject();
	objectManager.AddImage(exitbutton_obj, exitbutton1);
	exitbutton_obj->transform.position = { (float)AEGetWindowWidth() / 8, (float)AEGetWindowHeight() / -8, };
}

void StarBangBang::Main_Menu::Update()
{
	Scene::Update();

	if (tf == false)
	{
		objectManager.AddImage(settingsbutton_obj, settingsbutton1);
	}
	else
	{
		objectManager.AddImage(settingsbutton_obj, settingsbutton2);
	}


	if (AEInputCheckTriggered(VK_SPACE))
	{
		tf = true;
	}

	if (AEInputCheckTriggered(VK_F1))
	{
		tf = false;
	}
}

void StarBangBang::Main_Menu::Draw()
{
	Scene::Draw();
}

void StarBangBang::Main_Menu::Free()
{
	Scene::Free();
}

void StarBangBang::Main_Menu::Unload()
{
	Scene::Unload();
}


