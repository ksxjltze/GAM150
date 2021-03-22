#pragma once
#include "State.h"

#include "MovementManager.h"
#include "MessageBus.h"
#include "PlayerScript.h"
#include "CameraComponent.h"
#include "RigidBody.h"
#include "PrimaryMovementController.h"
#include "DetectionListener.h"
#include "Text.h"
#include "ComputerScript.h"

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

		static void SpawnPlayer(ObjectManager& objMgr, GameObject*& player, Sprite playerImage);
		static void SpawnClient(ObjectManager& objMgr, GameObject*& client, Sprite clientImage);
		static void SpawnComputer(ObjectManager& objMgr, Sprite playerImage, AEVec2 position);

	private:
		GameObject* player;
	};

}