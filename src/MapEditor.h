#pragma once
#include "TileManager.h"
#include "GameStateManager.h"
#include "MemoryManager.h"

namespace StarBangBang
{
	class MapEditor : public State
	{
	public:
		MapEditor(GameStateManager* manager, int id);
		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();
	private:
		TileManager tileManager;
		GameObject* tileMap;

		GameStateManager* gameStateManager;
		ObjectManager objectManager;
		GraphicsManager graphicsManager;
		MemoryManager memoryManager{ &objectManager, &graphicsManager };
	};
}