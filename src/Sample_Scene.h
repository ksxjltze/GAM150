#pragma once
#include "State.h"
#include "Player.h"

namespace StarBangBang
{
	class Sample_Scene : public State
	{
	public:
		Sample_Scene(int id, GameStateManager& manager);
		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();
	private:
		Sprite image;
		GameObject* gameObject;
	};
}