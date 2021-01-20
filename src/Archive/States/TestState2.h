#pragma once
#include "State.h"
#include "ObjectManager.h"
#include "GameStateManager.h"
#include "Sprite.h"
#include "MemoryManager.h"

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
		Sprite sprite;
		MemoryManager memoryManager { &objectManager, &graphicsManager };
		ObjectManager objectManager;
		GraphicsManager graphicsManager;
		GameStateManager* gameStateManager;
		GameObject* object1;
	};
}