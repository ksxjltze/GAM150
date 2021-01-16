#pragma once
#include "State.h"
#include "AEEngine.h"
#include "TestObject.h"
#include "Tilemap.h"
#include "ObjectManager.h"
#include "ImageComponent.h"

namespace StarBangBang
{
	class TestState : public State
	{
	public:
		TestState();
		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();

	private:
		GraphicsManager graphicsManager;
		ObjectManager objectManager;

		Image* objectImage;
		Image* tileImage;

		GameObject* object;
		GameObject* object2;

		Tilemap tilemap;
		float camX = 0, camY = 0;
		s8 fontId = 0;
	};

}