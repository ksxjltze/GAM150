#pragma once
#include "Settings.h"

namespace StarBangBang
{
	class ConfirmationMenu : public SettingsMenu
	{
	public:
		ConfirmationMenu(GameObject* gameObject, GraphicsManager& gfx);
		void Init();
		void Toggle();
	private:
		void Confirm();
		void Back();

		GameObject* confirmBtn{ nullptr };
		GameObject* backBtn{ nullptr };
	};
}