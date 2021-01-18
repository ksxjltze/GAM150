#pragma once
#include "State.h"
#include "ObjectManager.h"
#include "GameStateManager.h"

namespace StarBangBang
{
	class TestState2 : public State
	{
	public:
		TestState2(GameStateManager* gameStateManager, int id);
		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();
	private:
		ObjectManager objectManager;
		GraphicsManager graphicsManager;
		GameStateManager* gameStateManager;
		GameObject* object1;
	};
}