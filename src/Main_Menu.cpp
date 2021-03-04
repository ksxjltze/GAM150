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
	startgame_button = graphicsManager.CreateSprite(RESOURCES::STARTGAME_BUTTON_PATH);
	settings_button = graphicsManager.CreateSprite(RESOURCES::SETTINGS_BUTTON_PATH);
	credits_button = graphicsManager.CreateSprite(RESOURCES::CREDITS_BUTTON_PATH);
	exitgame_button = graphicsManager.CreateSprite(RESOURCES::EXITGAME_BUTTON_PATH);
}

void StarBangBang::Main_Menu::Init()
{
	//start game button
	startbutton_obj = objectManager.NewGameObject();
	objectManager.AddImage(startbutton_obj, startgame_button);
	startbutton_obj->transform.scale = { x_scale,y_scale };
	startbutton_obj->transform.position = { 100,100 };

	//settings button
	settingsbutton_obj = objectManager.NewGameObject();
	objectManager.AddImage(settingsbutton_obj, settings_button);
	//settingsbutton_obj->transform.scale = { x_scale,y_scale };

	//credits button
	creditsbutton_obj = objectManager.NewGameObject();
	objectManager.AddImage(creditsbutton_obj, credits_button);
	//creditsbutton_obj->transform.scale = { x_scale,y_scale };

	//exit game button
	exitbutton_obj = objectManager.NewGameObject();
	objectManager.AddImage(exitbutton_obj, exitgame_button);
	//exitbutton_obj->transform.scale = { x_scale,y_scale };
}

void StarBangBang::Main_Menu::Update()
{
	Scene::Update();
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
	Scene::Free();
}


