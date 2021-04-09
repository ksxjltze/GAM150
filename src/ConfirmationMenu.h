#pragma once
#include "Settings.h"

namespace StarBangBang
{
	class GameStateManager;
	class ConfirmationMenu : public Menu
	{
	public:
		ConfirmationMenu(GameObject* gameObject, GraphicsManager& gfx, GameStateManager& gsm);
		void Init();
		void Toggle();
	private:
		void Confirm();
		void Back();

		GameStateManager& gsm;
		GameObject* confirmBtn{ nullptr };
		GameObject* backBtn{ nullptr };
	};
}