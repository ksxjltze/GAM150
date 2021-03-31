#include "DoorTest.h"

#include "Door.h"
#include "Key.h"

#include "CameraComponent.h"
#include "PrimaryMovementController.h"

namespace StarBangBang
{
	static Sprite doorSprite;
	static Sprite keySprite;
	static Sprite playerSprite;

	DoorTest::DoorTest(int id, GameStateManager& manager) : Scene(id, manager)
	{

	}

	void DoorTest::Load()
	{
		doorSprite = graphicsManager.CreateSprite(RESOURCES::DOOR_PATH);
		keySprite = graphicsManager.CreateSprite(RESOURCES::KEY_PATH);
		playerSprite = graphicsManager.CreateSprite(RESOURCES::CAPTAINSTEALTH_F1_PATH);
	}

	void DoorTest::Init()
	{
		//Door
		GameObject* doorObj = objectManager.NewGameObject();
		objectManager.AddImage(doorObj, doorSprite);

		Door* door = &objectManager.AddComponent<Door>(doorObj);
		doorObj->transform.position = { 100, 0 };
		objectManager.AddCollider(doorObj, true).rb->SetMass(0);


		//Key
		GameObject* key = objectManager.NewGameObject();
		objectManager.AddImage(key, keySprite);

		objectManager.AddComponent<Key>(key, door);
		key->transform.position = { -100, 0 };
		objectManager.AddCollider(key, true).isTrigger = true;

		//Key2
		GameObject* key2 = objectManager.NewGameObject();
		objectManager.AddImage(key2, keySprite);

		objectManager.AddComponent<Key>(key2, door);
		key2->transform.position = { -100, 150 };
		objectManager.AddCollider(key2, true).isTrigger = true;

		GameObject* player;
		player = objectManager.NewGameObject();
		player->name = "Player";
		player->transform.scale = { 0.7f, 0.7f };

		objectManager.AddImage(player, playerSprite);

		objectManager.AddComponent<CameraComponent>(player);

		objectManager.AddComponent<PrimaryMovementController>(player);
		objectManager.AddCollider(player, false);

	}

	void DoorTest::Update()
	{
		Scene::Update();
	}

	void DoorTest::Draw()
	{
		Scene::Draw();
	}

	void DoorTest::Free()
	{
		Scene::Free();
	}

	void DoorTest::Unload()
	{
		Scene::Unload();
	}
}