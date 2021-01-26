#pragma once
#include "State.h"
#include "GameStateManager.h"

namespace StarBangBang
{
	class TestScene : public State
	{
	public:
		TestScene(GameStateManager* manager, int id);
		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();
	private:
		Sprite testSprite;
		std::vector<GameObject*> gameObjects;
		GameStateManager* gameStateManager;
	};
}