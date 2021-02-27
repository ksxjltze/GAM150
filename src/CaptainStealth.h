#pragma once
#include "State.h"

namespace StarBangBang
{
	class CaptainStealth : public Scene
	{
	public:
		CaptainStealth(int id, GameStateManager& gsm);
		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();
	};

}