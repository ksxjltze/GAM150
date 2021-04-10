#pragma once
#include "State.h"

#include "MovementManager.h"
#include "MessageBus.h"
#include "PlayerScript.h"
#include "CameraComponent.h"
#include "PrimaryMovementController.h"
#include "Text.h"
#include "Door.h"

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

		static void SpawnPlayer(ObjectManager& objMgr, GameObject*& player,Sprite image);
		static void SpawnClient(ObjectManager& objMgr, GameObject*& client, Sprite image);
		static Door* SpawnDoor(ObjectManager& objMgr, Sprite image, AEVec2 position);
		static void SpawnKey(ObjectManager& objMgr, Door* door, Sprite image, AEVec2 position);

	private:
		GameObject* player;
	};

}