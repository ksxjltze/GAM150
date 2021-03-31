#pragma once
#include "State.h"
#include "ObjectManager.h"
#include "GraphicsManager.h"
#include "GameStateManager.h"



namespace StarBangBang
{
	class LogoSplash : public Scene
	{
	public:
		
		LogoSplash(int id, GameStateManager& gsm);
		void Load();
		void Init();
		void Draw();
		void Update();


	};
}