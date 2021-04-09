#pragma once
#include "Settings.h"

namespace StarBangBang
{
	class GameStateManager;
	class ConfirmationMenu : public Menu
	{
	public:
		ConfirmationMenu(GameObject* gameObject, GraphicsManager& gfx, GameStateManager& gsm, int type = 0);
		void Init();
		void Toggle();
		void SetText(std::string s);
	private:
		void Confirm();
		void Back();

		GameStateManager& gsm;
		GameObject* confirmBtn{ nullptr };
		GameObject* backBtn{ nullptr };
		int type{ 0 };
	};
}