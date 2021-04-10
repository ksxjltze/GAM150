#pragma once
#include "ScriptComponent.h"
#include "GraphicsManager.h"

namespace StarBangBang
{
	class Menu : public Script
	{
	public:
		Menu(GameObject* gameObject, GraphicsManager& gfx);
		virtual void Init() = 0;
		virtual void Toggle() = 0;
		void Start();
		void Draw();
		void ForceUpdate();
		void SetStatus(bool);
		bool GetStatus() { return status; }
	protected:
		std::vector<GameObject*> buttonList;
		GraphicsManager& gfxMgr;
	private:
		bool status{ false };
	};
}