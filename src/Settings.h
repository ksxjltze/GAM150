#pragma once
#include "ScriptComponent.h"
#include "GraphicsManager.h"

namespace StarBangBang
{
	class SettingsMenu : public Script
	{
	public:
		SettingsMenu(GameObject* gameObject, GraphicsManager& gfx);
		void Init();
		void Start();
		void Draw();
		void ForceUpdate();
		void Update();
		void Toggle();
		void SetStatus(bool);
		bool GetStatus() {return status;}
	private:
		bool status{ false };
		void Back();
		void Mute();
		void Fullscreen();

		std::vector<GameObject*> buttonList;

		GameObject* muteBtn{ nullptr };
		GameObject* fullscreenBtn{ nullptr };
		GameObject* backBtn{ nullptr };
		GraphicsManager& gfxMgr;
	};
}