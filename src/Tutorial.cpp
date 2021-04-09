/*!*********************************************************************
\file     Tutorial.cpp
\author   Liew Ruiheng Rayner
\par      DP email: r.liew\@digipen.edu
\date     08/04/2021

\brief
  This file contains the Tutorial scene class
***********************************************************************/

#include "Tutorial.h"
#include "Text.h"
#include "globals.h"
#include "CameraComponent.h"
#include "Click.h"
#include "UIComponent.h"
#include "PrimaryMovementController.h"
#include "PlayerAnimation.h"
#include "MovementManager.h"
#include "Disappear.h"
#include "CaptainStealth.h"

static int animation_counter = 0;
static float app_time = 0.0f;

using namespace StarBangBang;
Sprite stealth_icon;
Sprite playerImageR1;
Sprite playerImageR2;
Sprite playerImageR3;
Sprite playerImageL1;
Sprite playerImageL2;
Sprite playerImageL3;
Sprite vent_close;

static StarBangBang::AnimationSprites animSprites;

void Tutorial::NewTextObject(AEVec2 position, const std::string& s, float scale)
{
	objectManager.AddComponent<Text>(objectManager.NewGameObject(), s, fontId2, scale).gameObject->transform.position = position;
}

Tutorial::Tutorial(int id, GameStateManager& gsm) 
	: Scene(id, gsm)
	, cameraObject(nullptr)
	, end(nullptr)
	, tilemap{ objectManager, graphicsManager }
{
	dir = direction::idle;
	character = current_char::fei_ge;
}

void Tutorial::Load()
{
	tilemap.Load(RESOURCES::LEVELS::LEVEL_TUTORIAL);
	tutorialSprite  = graphicsManager.CreateSprite(RESOURCES::TUTORIAL_BUTTON_PATH);
	movementSprite  = graphicsManager.CreateSprite(RESOURCES::ARROWKEYS_PATH);
	tabSprite       = graphicsManager.CreateSprite(RESOURCES::TABBUTTON_PATH);
	ventSprite		= graphicsManager.CreateSprite(RESOURCES::VENT_OPEN_PATH);
	vent_close = graphicsManager.CreateSprite(RESOURCES::VENT_CLOSE_PATH);
	distractSprite  = graphicsManager.CreateSprite(RESOURCES::VENDING_LEFT_PATH);
	distractSprite2 = graphicsManager.CreateSprite(RESOURCES::COMPUTER_PATH);
	backSprite      = graphicsManager.CreateSprite(RESOURCES::BACK_BUTTON_PATH);
	stealth_icon		= graphicsManager.CreateSprite(RESOURCES::EYE_SPRITE_PATH);

	animSprites.Load(graphicsManager);
}

void Tutorial::Init()
{
	animation_counter = 0;
	app_time = 0.0f;

	CaptainStealth::SpawnClient(objectManager, player2, graphicsManager.CreateSprite(RESOURCES::PRISONER_F1_PATH));
	CaptainStealth::SpawnPlayer(objectManager, player, graphicsManager.CreateSprite(RESOURCES::CAPTAINSTEALTH_F1_PATH));
	player->transform.position = { -250.0f, -110.0f };
	player2->transform.position = { 0.0f, 0.0f };
	player2->SetLayer(FOREGROUND);
	MovementManager& movementMgr = objectManager.AddComponent<MovementManager>(player);
	movementMgr.AddController(player);
	movementMgr.AddController(player2);

	float spacing = 100.f;
	float offset = 0.f;

	//if (GRAPHICS::IsFullscreen())
	offset = spacing;

	AEVec2 pos = { 0.0f, 120.0f };

	GRAPHICS::SetBackgroundColor(Black);

	ImageComponent* tutorialImg = objectManager.AddImage(objectManager.NewGameObject(), tutorialSprite);
	tutorialImg->gameObject->SetPos({ 0, 230 });
	tutorialImg->gameObject->transform.scale = { 2.0f, 1.0f };

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
	objectManager.AddComponent<ImageComponent>(UI, stealth_icon);
	UI->transform.position = { -240, -170 };

	UI = objectManager.NewGameObject();
	NewTextObject({ -240, -210 }, "Use [Q] to enter stealth mode", 0.3f);
	UIComponent& UICom = objectManager.AddComponent<UIComponent>(UI, stealth_icon, graphicsManager);
	UICom.rescale = false;
	UICom.gameObject->SetLayer(LAYER::UI);
	UICom.SetColor(Color{ 1.0f,1.0f,1.0f,0.7f });
	Text& uiText = objectManager.AddComponent<Text>(objectManager.NewGameObject(), "Q", fontId, White, 1.0f, false);
	uiText.gameObject->transform.position = { 0.05f, 0.28f };
	uiText.SetOffset({ -1.0f, -1.0f });
	UI->transform.position = { -AEGetWindowWidth() / 2 + 0.05f * AEGetWindowWidth(), -AEGetWindowHeight() / 2 + 0.1f * AEGetWindowHeight() };
	uiText.gameObject->name = "Stealth_Txt";
	UI->name = "Stealth_UI";

	NewTextObject({ 230, 0 }, "<INTERACTABLES>", 1.f);
	ImageComponent* ventImg = objectManager.AddImage(objectManager.NewGameObject(), ventSprite);
	ventImg->gameObject->SetPos({ 130 + offset, -50 });
	objectManager.AddCollider(ventImg->gameObject, true).isTrigger = true;
	objectManager.AddComponent<Disappear>(ventImg->gameObject, ventSprite, vent_close);
	NewTextObject({ 120 + offset, -100 }, "Enter vents to hide from guards", 0.3f);

	ImageComponent* distractImg = objectManager.AddImage(objectManager.NewGameObject(), distractSprite);
	distractImg->gameObject->SetPos({ 100 + offset, -160 });
	ImageComponent* distractImg2 = objectManager.AddImage(objectManager.NewGameObject(), distractSprite2);
	distractImg2->gameObject->SetPos({ 170 + offset, -170 });
	NewTextObject({ 120 + offset, -210 }, "Touch objects to distract guards", 0.3f);

	GameObject* backButton = objectManager.NewGameObject();
	objectManager.AddImage(backButton, backSprite);
	backButton->transform.position = { 0, -230 };
	backButton->transform.scale = { 1, 0.5f };
	objectManager.AddComponent<Click<Tutorial>>(backButton).setCallback(*this, &Tutorial::MainMenu);
}

void Tutorial::Update()
{
	if (AEInputCheckTriggered(AEVK_ESCAPE))
	{
		gameStateManager.SetNextGameState(MAIN_MENU);
		return;
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

	if (!(AEInputCheckCurr(KEYBIND::MOVEMENT_UP) || AEInputCheckCurr(KEYBIND::MOVEMENT_DOWN) ||
		AEInputCheckCurr(KEYBIND::MOVEMENT_LEFT) || AEInputCheckCurr(KEYBIND::MOVEMENT_RIGHT) ||
		AEInputCheckCurr(KEYBIND::MOVEMENT_UP_ALT) || AEInputCheckCurr(KEYBIND::MOVEMENT_DOWN_ALT) ||
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

	else if (AEInputCheckCurr(KEYBIND::MOVEMENT_UP) ||
		AEInputCheckCurr(KEYBIND::MOVEMENT_DOWN) ||
		AEInputCheckCurr(KEYBIND::MOVEMENT_UP_ALT) ||
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
