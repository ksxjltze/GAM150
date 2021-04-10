#pragma once
#include "State.h"

namespace StarBangBang
{
	class Scene_GameOver : public Scene
	{
	public:
		Scene_GameOver(int id, GameStateManager& gsm);
		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();
	private:
		void Quit();
		void Restart();
		GameObject* quitBtn;
		GameObject* restartBtn;
	};

}