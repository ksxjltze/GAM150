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

StarBangBang::ConfirmationMenu::ConfirmationMenu(GameObject* gameObject, GraphicsManager& gfx, GameStateManager& gsm) : Menu{ gameObject, gfx }, gsm{ gsm }
{

}

void StarBangBang::ConfirmationMenu::Init()
{
	confirmBtnSprite = gfxMgr.CreateSprite(RESOURCES::COMPUTER_PATH);
	backBtnSprite = gfxMgr.CreateSprite(RESOURCES::BACK_BUTTON_PATH);;

	const static AEVec2 btnScale{ 0.2f, 0.12f };

	confirmBtn = objMgr->NewGameObject();
	backBtn = objMgr->NewGameObject();

	confirmBtn->parent = gameObject;
	backBtn->parent = gameObject;

	objMgr->AddComponent<UIComponent>(gameObject, gfxMgr).SetColor({ 0.0f, 0.0f, 0.0f, 0.3f });
	gameObject->GetComponent<UIComponent>()->active = false;
	gameObject->transform.scale.x = AEGetWindowWidth() * 0.85f / GRAPHICS::MESH_WIDTH;
	gameObject->transform.scale.y = AEGetWindowHeight() * 0.85f / GRAPHICS::MESH_HEIGHT;

	objMgr->AddComponent<UIComponent>(backBtn, backBtnSprite, gfxMgr);
	objMgr->AddComponent<Click<ConfirmationMenu>>(backBtn, true).setCallback(*this, &ConfirmationMenu::Back);
	backBtn->transform.position = { 0.15f * gameObject->transform.scale.y * GRAPHICS::MESH_HEIGHT, 0.0f };
	backBtn->transform.scale.x = btnScale.x * gameObject->transform.scale.x;
	backBtn->transform.scale.y = btnScale.y * gameObject->transform.scale.y;
	backBtn->visible = false;

	objMgr->AddComponent<UIComponent>(confirmBtn, confirmBtnSprite, gfxMgr);
	objMgr->AddComponent<Click<ConfirmationMenu>>(confirmBtn, true).setCallback(*this, &ConfirmationMenu::Confirm);
	confirmBtn->transform.position = { -0.15f * gameObject->transform.scale.y * GRAPHICS::MESH_HEIGHT, 0.0f };
	confirmBtn->transform.scale.x = btnScale.x * gameObject->transform.scale.x;
	confirmBtn->transform.scale.y = btnScale.y * gameObject->transform.scale.y;
	confirmBtn->visible = false;

	buttonList.push_back(confirmBtn);
	buttonList.push_back(backBtn);

	Text& text = objMgr->AddComponent<Text>(gameObject, "Exit the game?", fontId2);
	text.SetOffset({ 0.0f, 100.0f });
	text.SetScale(2.0f);
	backBtn->SetLayer(UI);
	confirmBtn->SetLayer(UI);

}

void StarBangBang::ConfirmationMenu::Toggle()
{
	active = !active;
	gameObject->active = active;
	confirmBtn->active = active;
	backBtn->active = active;
}

void StarBangBang::ConfirmationMenu::Confirm()
{
	gsm.ExitGame();
}

void StarBangBang::ConfirmationMenu::Back()
{
	SetStatus(false);
}
