#pragma once
#include "ScriptComponent.h"
#include "GraphicsManager.h"

namespace StarBangBang
{
	class Settings : Script
	{
	public:
		Settings(GameObject* gameObject, GraphicsManager& gfx);
		void Start();
		void Update();
	private:
		GameObject* muteBtn;
		GameObject* fullscreenBtn;
		GraphicsManager& gfxMgr;
	};
}