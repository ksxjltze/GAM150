#pragma once
#include "State.h"

namespace StarBangBang
{
	class TestScene : public Scene
	{
	public:
		TestScene(int id, GameStateManager& gsm);
		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();
	};
}