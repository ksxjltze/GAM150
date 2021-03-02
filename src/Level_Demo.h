#pragma once
#include "State.h"
#include "ObjectManager.h"
#include "GraphicsManager.h"
#include "MemoryManager.h"
#include "GameStateManager.h"
#include "Player.h"
#include "GuardManager.h"
#include "TileMap.h"

namespace StarBangBang
{
	class Level_Demo : public Scene
	{
	public:
		Level_Demo(int id, GameStateManager& manager);
		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();
	private:
		Sprite playerImage;
		Sprite player2Image;
		Sprite planetImage;

		GameObject* movementController;
		GameObject* player;
		GameObject* player2;

		GameObject* testInteractable;
		GameObject* testGuard;
		GameObject* guardManager;

		std::vector<GameObject*> testObjects;

		TileMap tilemap;
	};
}