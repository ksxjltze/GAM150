#pragma once
#include "State.h"

namespace StarBangBang
{
	class EngineProof : public Scene
	{
	public:
		EngineProof(int id, GameStateManager& manager);
		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();

	private:
		void SpawnObject();
	};
}