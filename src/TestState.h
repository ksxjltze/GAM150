#pragma once
#include "State.h"
#include "AEEngine.h"
#include "TestObject.h"
#include "Tilemap.h"

namespace TempTeam
{
	class TestState : public State
	{
	public:
		TestState();
		void Init();
		void Update();
		void Draw();
		void Exit();

	private:
		TestObject object;
		Tilemap tilemap;
		float camX = 0, camY = 0;
		s8 fontId = 0;
	};

}