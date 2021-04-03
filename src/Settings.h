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
		void Update();
		void Toggle();
	private:
		GameObject* muteBtn{ nullptr };
		GameObject* fullscreenBtn{ nullptr };
		GraphicsManager& gfxMgr;
	};
}