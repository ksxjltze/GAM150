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

	objMgr->AddComponent<UIComponent>(gameObject, gfxMgr);
	gameObject->transform.scale.x = AEGetWindowWidth() * 0.8 / GRAPHICS::MESH_WIDTH;
	gameObject->transform.scale.y = AEGetWindowHeight() * 0.8 / GRAPHICS::MESH_HEIGHT;

	objMgr->AddComponent<UIComponent>(muteBtn, gfxMgr).SetColor(Blue);
	objMgr->AddComponent<Text>(muteBtn, "Mute", fontId2, Black);

	muteBtn->transform.position = { -200, 0 };
	objMgr->AddComponent<UIComponent>(fullscreenBtn, gfxMgr).SetColor(Blue);
	objMgr->AddComponent<Text>(fullscreenBtn, "Fullscreen", fontId2, Black);
	fullscreenBtn->transform.position = { 200, 0 };

	Toggle();
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
