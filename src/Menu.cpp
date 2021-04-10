#include "Menu.h"

StarBangBang::Menu::Menu(GameObject* gameObject, GraphicsManager& gfx) : Script(gameObject), gfxMgr{ gfx }
{

}

void StarBangBang::Menu::Start()
{
	SetStatus(false);
}

void StarBangBang::Menu::Draw()
{
	if (gameObject->active)
	{
		for (auto& btnObj : buttonList)
		{
			for (auto& component : btnObj->GetComponents())
			{
				component->Draw();
			}
		}
	}
}

void StarBangBang::Menu::ForceUpdate()
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

void StarBangBang::Menu::SetStatus(bool s)
{
	status = s;
	gameObject->active = status;
	for (auto& btnObj : buttonList)
	{
		btnObj->active = status;
	}
}
