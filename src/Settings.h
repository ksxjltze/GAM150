#pragma once
#include "ScriptComponent.h"
#include "GraphicsManager.h"

namespace StarBangBang
{
	class SettingsMenu : public Script
	{
	public:
		SettingsMenu(GameObject* gameObject, GraphicsManager& gfx);
		virtual void Init();
		void Start();
		void Draw();
		void ForceUpdate();
		void Update();
		virtual void Toggle();
		void SetStatus(bool);
		bool GetStatus() {return status;}
	protected:
		virtual void Back();
		std::vector<GameObject*> buttonList;
		GraphicsManager& gfxMgr;
	private:
		bool status{ false };
		void Mute();
		void Fullscreen();

		GameObject* muteBtn{ nullptr };
		GameObject* fullscreenBtn{ nullptr };
		GameObject* backBtn{ nullptr };
	};
}