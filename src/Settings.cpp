/******************************************************************************/
/*!
\title		Captain Stealth
\file		Settings.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Settings Menu.
			Displays a settings menu (Overlay)
			Has buttons for muting sound and toggling fullscreen mode.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#include "Settings.h"
#include "ObjectManager.h"
#include "UIComponent.h"
#include "Text.h"
#include "globals.h"
#include "Click.h"

namespace StarBangBang
{
	const static AEVec2 btnScale{0.2f, 0.12f};
}

StarBangBang::SettingsMenu::SettingsMenu(GameObject* gameObject, GraphicsManager& gfx) : Menu(gameObject, gfx)
{

}

void StarBangBang::SettingsMenu::Init()
{
	//Load button sprites
	Sprite fullscreenBtnSprite = gfxMgr.CreateSprite(RESOURCES::FULLSCREEN_BUTTON_PATH);
	Sprite muteBtnSprite = gfxMgr.CreateSprite(RESOURCES::MUTE_BUTTON_PATH);
	Sprite backBtnSprite = gfxMgr.CreateSprite(RESOURCES::BACK_BUTTON_PATH);

	//Allocate Game Objects
	muteBtn = objMgr->NewGameObject();
	fullscreenBtn = objMgr->NewGameObject();
	backBtn = objMgr->NewGameObject();

	//Set parent
	muteBtn->parent = gameObject;
	fullscreenBtn->parent = gameObject;
	backBtn->parent = gameObject;

	//Background Overlay
	objMgr->AddComponent<UIComponent>(gameObject, gfxMgr).SetColor({ 0.0f, 0.0f, 0.0f, 0.3f });
	gameObject->GetComponent<UIComponent>()->active = false;
	gameObject->transform.scale.x = AEGetWindowWidth() * 0.85f / GRAPHICS::MESH_WIDTH;
	gameObject->transform.scale.y = AEGetWindowHeight() * 0.85f / GRAPHICS::MESH_HEIGHT;

	//Mute button
	objMgr->AddComponent<UIComponent>(muteBtn, muteBtnSprite, gfxMgr);
	objMgr->AddComponent<Click<SettingsMenu>>(muteBtn, true).setCallback(*this, &SettingsMenu::Mute);

	muteBtn->transform.position = { 0.0f, 0.15f * gameObject->transform.scale.x * GRAPHICS::MESH_HEIGHT };
	muteBtn->transform.scale.x = btnScale.x * gameObject->transform.scale.x;
	muteBtn->transform.scale.y = btnScale.y * gameObject->transform.scale.y;
	muteBtn->visible = false;

	//Fullscreen toggle button
	objMgr->AddComponent<UIComponent>(fullscreenBtn, fullscreenBtnSprite, gfxMgr);
	objMgr->AddComponent<Click<SettingsMenu>>(fullscreenBtn, true).setCallback(*this, &SettingsMenu::Fullscreen);
	fullscreenBtn->visible = false;

	fullscreenBtn->transform.position = { 0.0f, 0.0f };
	fullscreenBtn->transform.scale.x = btnScale.x * gameObject->transform.scale.x;
	fullscreenBtn->transform.scale.y = btnScale.y * gameObject->transform.scale.y;

	//Back button
	objMgr->AddComponent<UIComponent>(backBtn, backBtnSprite, gfxMgr);
	objMgr->AddComponent<Click<SettingsMenu>>(backBtn, true).setCallback(*this, &SettingsMenu::Back);
	backBtn->transform.position = { 0.0f, -0.15f * gameObject->transform.scale.x * GRAPHICS::MESH_HEIGHT };

	backBtn->transform.scale.x = btnScale.x * gameObject->transform.scale.x;
	backBtn->transform.scale.y = btnScale.y * gameObject->transform.scale.y;
	backBtn->visible = false;	

	//Add to list
	buttonList.push_back(muteBtn);
	buttonList.push_back(fullscreenBtn);
	buttonList.push_back(backBtn);

}

void StarBangBang::SettingsMenu::Toggle()
{
	active = !active;
	gameObject->active = active;
	muteBtn->active = active;
	fullscreenBtn->active = active;
}

void StarBangBang::SettingsMenu::Back()
{
	SetStatus(false);
}

void StarBangBang::SettingsMenu::Mute()
{
	MessageBus::Notify({ EventId::MUTE, ChannelGroupId::ALL });
}

void StarBangBang::SettingsMenu::Fullscreen()
{
	GRAPHICS::ToggleFullscreen();
}
