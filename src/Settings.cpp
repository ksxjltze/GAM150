#include "Settings.h"
#include "ObjectManager.h"
#include "UIComponent.h"
#include "Text.h"
#include "globals.h"

StarBangBang::SettingsMenu::SettingsMenu(GameObject* gameObject, GraphicsManager& gfx) : Script(gameObject), gfxMgr{ gfx }
{

}

void StarBangBang::SettingsMenu::Start()
{
	muteBtn = objMgr->NewGameObject();
	fullscreenBtn = objMgr->NewGameObject();

	muteBtn->parent = gameObject;
	fullscreenBtn->parent = gameObject;

	objMgr->AddComponent<UIComponent>(gameObject, gfxMgr).SetColor(Black);
	gameObject->transform.scale.x = AEGetWindowWidth() * 0.8 / GRAPHICS::MESH_WIDTH;
	gameObject->transform.scale.y = AEGetWindowHeight() * 0.8 / GRAPHICS::MESH_HEIGHT;

	objMgr->AddComponent<UIComponent>(muteBtn, gfxMgr).SetColor(White);
	objMgr->AddComponent<Text>(muteBtn, "Mute", fontId2, Black);

	muteBtn->transform.position = { -0.3f * gameObject->transform.scale.x * GRAPHICS::MESH_WIDTH, 0 };
	muteBtn->transform.scale.x = 0.2f * gameObject->transform.scale.x;
	muteBtn->transform.scale.y = 0.2f * gameObject->transform.scale.y;

	objMgr->AddComponent<UIComponent>(fullscreenBtn, gfxMgr).SetColor(White);
	objMgr->AddComponent<Text>(fullscreenBtn, "Fullscreen", fontId2, Black);

	fullscreenBtn->transform.position = { 0.2f * gameObject->transform.scale.x * GRAPHICS::MESH_WIDTH, 0 };
	fullscreenBtn->transform.scale.x = 0.4f * gameObject->transform.scale.x;
	fullscreenBtn->transform.scale.y = 0.2f * gameObject->transform.scale.y;

	SetStatus(false);
}

void StarBangBang::SettingsMenu::Update()
{

}

void StarBangBang::SettingsMenu::Toggle()
{
	active = !active;
	gameObject->active = active;
	muteBtn->active = active;
	fullscreenBtn->active = active;
}

void StarBangBang::SettingsMenu::SetStatus(bool status)
{
	gameObject->active = status;
	muteBtn->active = status;
	fullscreenBtn->active = status;
}
