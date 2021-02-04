#pragma once
#include "State.h"
#include "GameStateManager.h"
#include "Player.h"

namespace StarBangBang
{
	class Sample_Scene : public State
	{
	public:
		Sample_Scene(GameStateManager* manager, int id);
		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();
	private:
		Sprite image;
		GameObject* gameObject;
		GameStateManager* gameStateManager;
	};
}