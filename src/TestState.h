#pragma once
#include "State.h"
#include "AEEngine.h"
#include "ObjectManager.h"
#include "ImageComponent.h"
#include "TileManager.h"
#include "TestState2.h"
#include "GameStateManager.h"
#include "MemoryManager.h"

namespace StarBangBang
{
	class TestState : public State
	{
	public:
		TestState(GameStateManager* gameStateManager, int id);
		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();

	private:
		GameStateManager* gameStateManager;
		GraphicsManager graphicsManager;
		ObjectManager objectManager;
		MemoryManager memoryManager { &objectManager, &graphicsManager };
		TileManager tileManager;

		GameObject* object2;
		GameObject* object2Child;

		float camX = 0, camY = 0;
		s8 fontId = 0;
	};

}