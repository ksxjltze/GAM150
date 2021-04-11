/******************************************************************************/
/*!
\title		Captain Stealth
\file		ConfirmationMenu.cpp
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Confirmation Menu.
			Displays a confirmation menu for destructive actions.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#include "ConfirmationMenu.h"
#include "ObjectManager.h"
#include "UIComponent.h"
#include "Click.h"
#include "GameStateManager.h"
#include "Text.h"
#include "globals.h"

namespace StarBangBang
{
	Sprite confirmBtnSprite;
	Sprite backBtnSprite;
}

/*!*************************************************************************
 * \brief
 * Menu (Script) constructor.
 * \param gameObject
 * GameObject to attach to.
 * \param gfx
 * Reference to the graphics manager.
 * \param gsm
 * Reference to the game state manager.
 * \param type
 * Type of confirmation.
***************************************************************************/
StarBangBang::ConfirmationMenu::ConfirmationMenu(GameObject* gameObject, GraphicsManager& gfx, GameStateManager& gsm, int type) : Menu{ gameObject, gfx }, gsm{ gsm }, type{ type }
{

}

/*!*************************************************************************
 * \brief
 * Initializes the menu.
 * \return
 * void
***************************************************************************/
void StarBangBang::ConfirmationMenu::Init()
{
	//Load sprites
	confirmBtnSprite = gfxMgr.CreateSprite(RESOURCES::CONFIRM_BUTTON_PATH);
	backBtnSprite = gfxMgr.CreateSprite(RESOURCES::BACK_BUTTON_PATH);;

	const static AEVec2 btnScale{ 0.2f, 0.12f };

	//Create new game objects
	confirmBtn = objMgr->NewGameObject();
	backBtn = objMgr->NewGameObject();
	textObject = objMgr->NewGameObject();

	//Set parent
	confirmBtn->parent = gameObject;
	backBtn->parent = gameObject;
	textObject->parent = gameObject;

	//Background
	objMgr->AddComponent<UIComponent>(gameObject, gfxMgr).SetColor({ 0.0f, 0.0f, 0.0f, 0.3f });
	gameObject->GetComponent<UIComponent>()->active = false;

	gameObject->transform.scale.x = 1.5f * AEGetWindowWidth() / GRAPHICS::MESH_WIDTH;
	gameObject->transform.scale.y = 2 * AEGetWindowHeight() / GRAPHICS::MESH_HEIGHT;

	//Back button
	objMgr->AddComponent<UIComponent>(backBtn, backBtnSprite, gfxMgr);
	objMgr->AddComponent<Click<ConfirmationMenu>>(backBtn, true).setCallback(*this, &ConfirmationMenu::Back);

	backBtn->transform.position = { 0.15f * gameObject->transform.scale.y * GRAPHICS::MESH_HEIGHT, -100.0f };
	backBtn->transform.scale.x = btnScale.x * gameObject->transform.scale.x;
	backBtn->transform.scale.y = btnScale.y * gameObject->transform.scale.y;
	backBtn->visible = false;

	//Confirm button
	objMgr->AddComponent<UIComponent>(confirmBtn, confirmBtnSprite, gfxMgr);
	objMgr->AddComponent<Click<ConfirmationMenu>>(confirmBtn, true).setCallback(*this, &ConfirmationMenu::Confirm);

	confirmBtn->transform.position = { -0.15f * gameObject->transform.scale.y * GRAPHICS::MESH_HEIGHT, -100.0f };
	confirmBtn->transform.scale.x = btnScale.x * gameObject->transform.scale.x;
	confirmBtn->transform.scale.y = btnScale.y * gameObject->transform.scale.y;
	confirmBtn->visible = false;

	//Text
	Text& text = objMgr->AddComponent<Text>(textObject, "Are you sure?", fontId2, White, 1.0f, false);
	text.SetOffset({ 0.0f, 0.3f });
	backBtn->SetLayer(UI);
	confirmBtn->SetLayer(UI);

	//Add to list
	buttonList.push_back(confirmBtn);
	buttonList.push_back(backBtn);
	buttonList.push_back(textObject);
}

/*!*************************************************************************
 * \brief
 * Toggles the menu.
 * \return
 * void
***************************************************************************/
void StarBangBang::ConfirmationMenu::Toggle()
{
	active = !active;
	gameObject->active = active;
	confirmBtn->active = active;
	backBtn->active = active;
	textObject->active = active;
}

/*!*************************************************************************
 * \brief
 * Sets the text to display.
 * \param s
 * String to display.
***************************************************************************/
void StarBangBang::ConfirmationMenu::SetText(const std::string& s)
{
	textObject->GetComponent<Text>()->SetText(s);
}

/*!*************************************************************************
 * \brief
 * Confirm callback.
 * \return
 * void
***************************************************************************/
void StarBangBang::ConfirmationMenu::Confirm()
{
	switch (type)
	{
	case 0:
		gsm.ExitGame();
		break;
	case 1:
		gsm.SetNextGameState(MAIN_MENU);
		break;
	}
}

/*!*************************************************************************
 * \brief
 * Back callback.
 * \return
 * void
***************************************************************************/
void StarBangBang::ConfirmationMenu::Back()
{
	SetStatus(false);
}
