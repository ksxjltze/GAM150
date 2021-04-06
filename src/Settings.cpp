#include "Settings.h"
#include "ObjectManager.h"
#include "UIComponent.h"
#include "Text.h"
#include "globals.h"
#include "Click.h"

namespace StarBangBang
{
	const static AEVec2 btnScale{0.2f, 0.1f};
}

StarBangBang::SettingsMenu::SettingsMenu(GameObject* gameObject, GraphicsManager& gfx) : Script(gameObject), gfxMgr{ gfx }
{

}

void StarBangBang::SettingsMenu::Init()
{
	Sprite fullscreenBtnSprite = gfxMgr.CreateSprite(RESOURCES::FULLSCREEN_BUTTON_PATH);
	Sprite muteBtnSprite = gfxMgr.CreateSprite(RESOURCES::MUTE_BUTTON_PATH);

	muteBtn = objMgr->NewGameObject();
	fullscreenBtn = objMgr->NewGameObject();

	muteBtn->parent = gameObject;
	fullscreenBtn->parent = gameObject;
	//gameObject->visible = false;

	objMgr->AddComponent<UIComponent>(gameObject, gfxMgr).SetColor(Gray);
	gameObject->GetComponent<UIComponent>()->active = false;
	gameObject->transform.scale.x = AEGetWindowWidth() * 0.85 / GRAPHICS::MESH_WIDTH;
	gameObject->transform.scale.y = AEGetWindowHeight() * 0.85 / GRAPHICS::MESH_HEIGHT;

	objMgr->AddComponent<UIComponent>(muteBtn, muteBtnSprite, gfxMgr);
	objMgr->AddComponent<Text>(muteBtn, "Mute", fontId2, Black);
	objMgr->AddComponent<Click<SettingsMenu>>(muteBtn, true).setCallback(*this, &SettingsMenu::Mute);

	muteBtn->transform.position = { -0.2f * gameObject->transform.scale.x * GRAPHICS::MESH_WIDTH, 0 };
	muteBtn->transform.scale.x = btnScale.x * gameObject->transform.scale.x;
	muteBtn->transform.scale.y = btnScale.y * gameObject->transform.scale.y;
	muteBtn->visible = false;

	objMgr->AddComponent<UIComponent>(fullscreenBtn, fullscreenBtnSprite, gfxMgr);
	objMgr->AddComponent<Text>(fullscreenBtn, "Fullscreen", fontId2, Black);
	objMgr->AddComponent<Click<SettingsMenu>>(fullscreenBtn, true).setCallback(*this, &SettingsMenu::Fullscreen);
	fullscreenBtn->visible = false;

	fullscreenBtn->transform.position = { 0.2f * gameObject->transform.scale.x * GRAPHICS::MESH_WIDTH, 0 };
	fullscreenBtn->transform.scale.x = btnScale.x * gameObject->transform.scale.x;
	fullscreenBtn->transform.scale.y = btnScale.y * gameObject->transform.scale.y;

	buttonList.push_back(muteBtn);
	buttonList.push_back(fullscreenBtn);

}

void StarBangBang::SettingsMenu::Start()
{
	SetStatus(false);
}

void StarBangBang::SettingsMenu::Update()
{

}

void StarBangBang::SettingsMenu::Draw()
{
	if (gameObject->active)
	{
		gameObject->GetComponent<UIComponent>()->Draw();
		muteBtn->GetComponent<UIComponent>()->Draw();
		fullscreenBtn->GetComponent<UIComponent>()->Draw();
	}
}

void StarBangBang::SettingsMenu::ForceUpdate()
{
	if (!gameObject->active)
		return;

	for (auto& btnObj : buttonList)
	{
		for (auto& component : btnObj->GetComponents())
		{
			component->Update();
		}
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
