#pragma once
#include "State.h"
#include "AEEngine.h"
#include "TestObject.h"
#include "Tilemap.h"
#include "ObjectManager.h"

namespace TempTeam
{
	class TestState : public State
	{
	public:
		TestState();
		void Load();
		void Init();
		void Update();
		void Draw();
		void Exit();

	private:
		GraphicsManager graphicsManager;
		ObjectManager objectManager;
		GameObject* object;
		Tilemap tilemap;
		float camX = 0, camY = 0;
		s8 fontId = 0;
	};

}