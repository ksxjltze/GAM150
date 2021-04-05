#include "Settings.h"
#include "ObjectManager.h"
#include "UIComponent.h"
#include "Text.h"
#include "globals.h"
#include "Click.h"

StarBangBang::SettingsMenu::SettingsMenu(GameObject* gameObject, GraphicsManager& gfx) : Script(gameObject), gfxMgr{ gfx }
{

}

void StarBangBang::SettingsMenu::Start()
{
	muteBtn = objMgr->NewGameObject();
	fullscreenBtn = objMgr->NewGameObject();

	muteBtn->parent = gameObject;
	fullscreenBtn->parent = gameObject;
	//gameObject->visible = false;

	objMgr->AddComponent<UIComponent>(gameObject, gfxMgr).SetColor(Blue);
	gameObject->GetComponent<UIComponent>()->active = false;
	gameObject->transform.scale.x = AEGetWindowWidth() * 0.8 / GRAPHICS::MESH_WIDTH;
	gameObject->transform.scale.y = AEGetWindowHeight() * 0.8 / GRAPHICS::MESH_HEIGHT;

	objMgr->AddComponent<UIComponent>(muteBtn, gfxMgr).SetColor(White);
	objMgr->AddComponent<Text>(muteBtn, "Mute", fontId2, Black);
	objMgr->AddComponent<Click<SettingsMenu>>(muteBtn, true).setCallback(*this, &SettingsMenu::Mute);

	muteBtn->transform.position = { -0.3f * gameObject->transform.scale.x * GRAPHICS::MESH_WIDTH, 0 };
	muteBtn->transform.scale.x = 0.2f * gameObject->transform.scale.x;
	muteBtn->transform.scale.y = 0.2f * gameObject->transform.scale.y;
	muteBtn->visible = false;

	objMgr->AddComponent<UIComponent>(fullscreenBtn, gfxMgr).SetColor(White);
	objMgr->AddComponent<Text>(fullscreenBtn, "Fullscreen", fontId2, Black);
	objMgr->AddComponent<Click<SettingsMenu>>(fullscreenBtn, true).setCallback(*this, &SettingsMenu::Fullscreen);
	fullscreenBtn->visible = false;

	fullscreenBtn->transform.position = { 0.2f * gameObject->transform.scale.x * GRAPHICS::MESH_WIDTH, 0 };
	fullscreenBtn->transform.scale.x = 0.4f * gameObject->transform.scale.x;
	fullscreenBtn->transform.scale.y = 0.2f * gameObject->transform.scale.y;

	SetStatus(false);
}

void StarBangBang::SettingsMenu::Update()
{

}

void StarBangBang::SettingsMenu::Draw()
{
	if (gameObject->active)
	{
		printf("d"); 
		gameObject->GetComponent<UIComponent>()->Draw();
		muteBtn->GetComponent<UIComponent>()->Draw();
		fullscreenBtn->GetComponent<UIComponent>()->Draw();
	}
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

void StarBangBang::SettingsMenu::Mute()
{
	MessageBus::Notify({ EventId::MUTE });
}

void StarBangBang::SettingsMenu::Fullscreen()
{
	GRAPHICS::ToggleFullscreen();
}
