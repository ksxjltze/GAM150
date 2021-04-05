#pragma once
#include "ScriptComponent.h"
#include "GraphicsManager.h"

namespace StarBangBang
{
	class SettingsMenu : public Script
	{
	public:
		SettingsMenu(GameObject* gameObject, GraphicsManager& gfx);
		void Start();
		void Draw();
		void ForceUpdate();
		void Update();
		void Toggle();
		void SetStatus(bool);
	private:
		void Mute();
		void Fullscreen();

		std::vector<GameObject*> buttonList;

		GameObject* muteBtn{ nullptr };
		GameObject* fullscreenBtn{ nullptr };
		GraphicsManager& gfxMgr;
	};
}