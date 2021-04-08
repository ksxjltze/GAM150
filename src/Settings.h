#pragma once
#include "ScriptComponent.h"
#include "GraphicsManager.h"
#include "Menu.h"

namespace StarBangBang
{
	class SettingsMenu : public Menu
	{
	public:
		SettingsMenu(GameObject* gameObject, GraphicsManager& gfx);
		void Init();
		void Toggle();
	private:
		void Back();
		void Mute();
		void Fullscreen();

		GameObject* muteBtn{ nullptr };
		GameObject* fullscreenBtn{ nullptr };
		GameObject* backBtn{ nullptr };
	};
}