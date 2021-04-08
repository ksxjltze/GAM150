#include "ConfirmationMenu.h"
#include "ObjectManager.h"
#include "UIComponent.h"
#include "Click.h"

namespace StarBangBang
{
	Sprite confirmBtnSprite;
	Sprite backBtnSprite;
}

StarBangBang::ConfirmationMenu::ConfirmationMenu(GameObject* gameObject, GraphicsManager& gfx) : SettingsMenu{gameObject, gfx}
{

}

void StarBangBang::ConfirmationMenu::Init()
{
	const static AEVec2 btnScale{ 0.2f, 0.12f };

	confirmBtn = objMgr->NewGameObject();
	backBtn = objMgr->NewGameObject();

	objMgr->AddComponent<UIComponent>(gameObject, gfxMgr).SetColor({ 0.0f, 0.0f, 0.0f, 0.3f });
	gameObject->GetComponent<UIComponent>()->active = false;
	gameObject->transform.scale.x = AEGetWindowWidth() * 0.85f / GRAPHICS::MESH_WIDTH;
	gameObject->transform.scale.y = AEGetWindowHeight() * 0.85f / GRAPHICS::MESH_HEIGHT;

	objMgr->AddComponent<UIComponent>(backBtn, backBtnSprite, gfxMgr);
	objMgr->AddComponent<Click<ConfirmationMenu>>(backBtn, true).setCallback(*this, &ConfirmationMenu::Back);
	backBtn->transform.position = { -0.15f * gameObject->transform.scale.y * GRAPHICS::MESH_HEIGHT, 0.0f };
	backBtn->transform.scale.x = btnScale.x * gameObject->transform.scale.x;
	backBtn->transform.scale.y = btnScale.y * gameObject->transform.scale.y;
	backBtn->visible = false;

	objMgr->AddComponent<UIComponent>(confirmBtn, confirmBtnSprite, gfxMgr);
	objMgr->AddComponent<Click<ConfirmationMenu>>(confirmBtn, true).setCallback(*this, &ConfirmationMenu::Confirm);
	confirmBtn->transform.position = { 0.15f * gameObject->transform.scale.y * GRAPHICS::MESH_HEIGHT, 0.0f };
	confirmBtn->transform.scale.x = btnScale.x * gameObject->transform.scale.x;
	confirmBtn->transform.scale.y = btnScale.y * gameObject->transform.scale.y;
	confirmBtn->visible = false;

	buttonList.push_back(confirmBtn);
	buttonList.push_back(backBtn);

}

void StarBangBang::ConfirmationMenu::Toggle()
{
}

void StarBangBang::ConfirmationMenu::Confirm()
{
}

void StarBangBang::ConfirmationMenu::Back()
{
}
