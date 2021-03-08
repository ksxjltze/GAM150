#pragma once
#include "State.h"
#include "Player.h"

namespace StarBangBang
{
	class Sample_Scene : public Scene
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
		Sprite image2;
		GameObject* gameObject;
	};
}