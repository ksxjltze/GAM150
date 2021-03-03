#pragma once
#include "State.h"
#include "ObjectManager.h"
#include "GraphicsManager.h"
#include "MemoryManager.h"
#include "GameStateManager.h"

namespace StarBangBang
{
	class Main_Menu: public Scene
	{
	public:
		Main_Menu(int id, GameStateManager& manager);
		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();
	private:
		Sprite startgame_button;
		Sprite settings_button;
		Sprite credits_button;
		Sprite exitgame_button;
		GameObject* startbutton_obj;
		GameObject* settingsbutton_obj;
		GameObject* creditsbutton_obj;
		GameObject* exitbutton_obj;
	};
}