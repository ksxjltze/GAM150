#include "Settings.h"
#include "ObjectManager.h"
#include "UIComponent.h"

StarBangBang::Settings::Settings(GameObject* gameObject, GraphicsManager& gfx) : Script(gameObject), gfxMgr{ gfx }
{
	muteBtn = objMgr->NewGameObject();
	fullscreenBtn = objMgr->NewGameObject();
}

void StarBangBang::Settings::Start()
{
	objMgr->AddComponent<UIComponent>(muteBtn, gfxMgr);
	objMgr->AddComponent<UIComponent>(fullscreenBtn, gfxMgr);
}

void StarBangBang::Settings::Update()
{

}
