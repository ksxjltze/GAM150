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

		void LoadLevelTest();

	private:

		Sprite logo;
		Sprite playbutton1;
		Sprite settingsbutton1;
		Sprite creditsbutton1;
		Sprite exitbutton1;

		Sprite playbutton2;
		Sprite settingsbutton2;
		Sprite creditsbutton2;
		Sprite exitbutton2;

		GameObject* logo_obj;
		GameObject* playbutton_obj;
		GameObject* settingsbutton_obj;
		GameObject* creditsbutton_obj;
		GameObject* exitbutton_obj;

		boolean tf;
	};
}