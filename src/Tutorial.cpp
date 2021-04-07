#include "Tutorial.h"
#include "Text.h"
#include "globals.h"
#include "CameraComponent.h"
#include "Click.h"
#include "UIComponent.h"

using namespace StarBangBang;
Sprite eyeSprite;

void Tutorial::NewTextObject(AEVec2 position, const std::string& s, float scale)
{
	objectManager.AddComponent<Text>(objectManager.NewGameObject(), s, fontId2, scale).gameObject->transform.position = position;
}

Tutorial::Tutorial(int id, GameStateManager& gsm) : Scene(id, gsm), tilemap{ objectManager, graphicsManager }
{
}

void Tutorial::Load()
{
	tilemap.Load(RESOURCES::LEVELS::LEVEL_TUTORIAL);
	tutorialSprite  = graphicsManager.CreateSprite(RESOURCES::TUTORIAL_BUTTON_PATH);
	movementSprite  = graphicsManager.CreateSprite(RESOURCES::ARROWKEYS_PATH);
	tabSprite       = graphicsManager.CreateSprite(RESOURCES::TABBUTTON_PATH);
	ventSprite		= graphicsManager.CreateSprite(RESOURCES::VENT_OPEN_PATH);
	distractSprite  = graphicsManager.CreateSprite(RESOURCES::VENDING_LEFT_PATH);
	distractSprite2 = graphicsManager.CreateSprite(RESOURCES::COMPUTER_PATH);
	backSprite      = graphicsManager.CreateSprite(RESOURCES::BACK_BUTTON_PATH);
	eyeSprite		= graphicsManager.CreateSprite(RESOURCES::EYE_SPRITE_PATH);
}

void Tutorial::Init()
{
	GameObject* obj = objectManager.NewGameObject();
	obj->transform.scale = { 0.00001f, 0.00001f };
	objectManager.AddImage(obj, graphicsManager.CreateSprite(RESOURCES::BIN_PATH));

	float spacing = 100.f;
	float offset = 0.f;

	//if (GRAPHICS::IsFullscreen())
	offset = spacing;

	AEVec2 pos = { 0.0f, 120.0f };

	GRAPHICS::SetBackgroundColor(Black);

	ImageComponent* tutorialImg = objectManager.AddImage(objectManager.NewGameObject(), tutorialSprite);
	tutorialImg->gameObject->SetPos({ 0, 230 });
	tutorialImg->gameObject->transform.scale = { 2.f, 2.f };

	NewTextObject({ 0, 160 }, "<OBJECTIVE>", 1.f);
	NewTextObject({ 0, 120 }, "Collect keys in each room to proceed!", 0.5f);
	NewTextObject({ 0, 100 }, "Guide the prisoner out of the prison while avoiding guards and security cameras!", 0.5f);
	NewTextObject({ 0, 80 }, "Enter stealth mode to stay undetected! (Only for player)", 0.5f);

	NewTextObject({ -250, 0 }, "<CONTROLS>", 1.f);
	ImageComponent* movementImg = objectManager.AddImage(objectManager.NewGameObject(), movementSprite);
	movementImg->gameObject->SetPos({-250 - offset, -50});
	NewTextObject({ -250 - offset, -100 }, "Use arrow keys to move", 0.3f);

	ImageComponent* tabImg = objectManager.AddImage(objectManager.NewGameObject(), tabSprite);
	tabImg->gameObject->SetPos({ -150, -50 });
	NewTextObject({ -150, -100 }, "Use [TAB] to change characters", 0.3f);

	GameObject* UI = objectManager.NewGameObject();
	objectManager.AddComponent<UIComponent>(UI, eyeSprite, graphicsManager);
	UI->transform.position = { -500, -340 };
	UI->transform.scale = { 2.0f, 2.0f};
	NewTextObject({ -240, -210 }, "Use [Q] to enter stealth mode", 0.3f);

	NewTextObject({ 230, 0 }, "<INTERACTABLES>", 1.f);
	ImageComponent* ventImg = objectManager.AddImage(objectManager.NewGameObject(), ventSprite);
	ventImg->gameObject->SetPos({ 130 + offset, -50 });
	NewTextObject({ 120 + offset, -100 }, "Enter vents to hide from guards", 0.3f);

	ImageComponent* distractImg = objectManager.AddImage(objectManager.NewGameObject(), distractSprite);
	distractImg->gameObject->SetPos({ 100 + offset, -160 });
	ImageComponent* distractImg2 = objectManager.AddImage(objectManager.NewGameObject(), distractSprite2);
	distractImg2->gameObject->SetPos({ 170 + offset, -170 });
	NewTextObject({ 120 + offset, -210 }, "Touch objects to distract guards", 0.3f);

	GameObject* backButton = objectManager.NewGameObject();
	objectManager.AddImage(backButton, backSprite);
	backButton->transform.position = { 0, -230 };
	backButton->transform.scale = { 1, 1 };
	objectManager.AddComponent<Click<Tutorial>>(backButton).setCallback(*this, &Tutorial::MainMenu);
}

void Tutorial::Update()
{
	if (AEInputCheckTriggered(AEVK_ESCAPE))
	{
		gameStateManager.SetNextGameState(MAIN_MENU);
		return;
	}

	Scene::Update();
}

void Tutorial::Draw()
{
	Scene::Draw();
}

void Tutorial::Free()
{
	Scene::Free();
	tilemap.Unload();
}

void Tutorial::Unload()
{
	Scene::Unload();
}

void Tutorial::MainMenu()
{
	gameStateManager.SetNextGameState(MAIN_MENU);
}
