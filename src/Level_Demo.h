#pragma once
#include "State.h"
#include "ObjectManager.h"
#include "GraphicsManager.h"
#include "MemoryManager.h"
#include "GameStateManager.h"

namespace StarBangBang
{
	class Level_Demo : public State
	{
	public:
		Level_Demo(GameStateManager* manager, int id);
		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();
	private:
		GameStateManager* gameStateManager;
	};
}