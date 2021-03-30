#pragma once
#include "State.h"

namespace StarBangBang
{
	class Credits : public Scene
	{
	public:
		Credits(int id, GameStateManager& gsm);
		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();
	private:
		GameObject* cameraObject{ nullptr };
	};

}