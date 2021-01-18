#pragma once
#include "State.h"
#include "AEEngine.h"
#include "TestObject.h"
#include "Tilemap.h"
#include "ObjectManager.h"
#include "ImageComponent.h"
#include "TileManager.h"
#include "TestState2.h"
#include "GameStateManager.h"

namespace StarBangBang
{
	class TestState : public State
	{
	public:
		TestState(GameStateManager* gameStateManager);
		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();

	private:
		GameStateManager* gameStateManager;
		GraphicsManager graphicsManager;
		ObjectManager objectManager;
		TileManager tileManager;

		Image* objectImage;
		Image* tileImage;

		GameObject* object;
		GameObject* object2;
		GameObject* object2Child;

		Tilemap tilemap;
		float camX = 0, camY = 0;
		s8 fontId = 0;
	};

}