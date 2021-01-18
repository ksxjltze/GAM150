#pragma once
#include "State.h"
#include "ObjectManager.h"
#include "GameStateManager.h"

namespace StarBangBang
{
	class TestState2 : public State
	{
	public:
		TestState2(GameStateManager* gameStateManager);
		virtual void Load();
		virtual void Init();
		virtual void Update();
		virtual void Draw();
		virtual void Free();
		virtual void Unload();
	private:
		ObjectManager objectManager;
		GraphicsManager graphicsManager;
		GameStateManager* gameStateManager;
		GameObject* object1;
	};
}