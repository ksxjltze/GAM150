#pragma once
#include "State.h"

namespace StarBangBang
{
	class DoorTest : public Scene
	{
	public:
		DoorTest(int id, GameStateManager& manager);
		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();

	};
}