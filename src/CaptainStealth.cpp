#include "CaptainStealth.h"
#include "globals.h"
#include "constants.h"
#include "Door.h"

namespace StarBangBang
{
	static Sprite playerSprite;

	StarBangBang::CaptainStealth::CaptainStealth(int id, GameStateManager& gsm) : Scene(id, gsm), player{ nullptr }
	{

	}

	void StarBangBang::CaptainStealth::Load()
	{
		playerSprite = graphicsManager.CreateSprite(RESOURCES::SPRITE_PLAYER_PATH);
	}

	void StarBangBang::CaptainStealth::Init()
	{

	}

	void StarBangBang::CaptainStealth::Update()
	{
		Scene::Update();
	}

	void StarBangBang::CaptainStealth::Draw()
	{
		Scene::Draw();
	}

	void StarBangBang::CaptainStealth::Free()
	{
		Scene::Free();
	}

	void StarBangBang::CaptainStealth::Unload()
	{
		Scene::Unload();
	}

	void CaptainStealth::SpawnComputer(ObjectManager& objMgr, Sprite computerSprite, AEVec2 position)
	{
		GameObject* gameObjPtr;
		//computer obj (v machine)
		gameObjPtr = objMgr.NewGameObject();
		objMgr.AddComponent<ComputerScript>(gameObjPtr);
		objMgr.AddImage(gameObjPtr, computerSprite);
		gameObjPtr->transform.position = position;

		//Add Collider
		Collider& collider = objMgr.AddCollider(gameObjPtr, false);
		collider.isTrigger = true;
	}

	Door* CaptainStealth::SpawnDoor(ObjectManager& objMgr, Sprite image, AEVec2 position)
	{
		GameObject* doorObj = objMgr.NewGameObject();
		Door& door = objMgr.AddComponent<Door>(doorObj);
		objMgr.AddImage(doorObj, image);
		doorObj->transform.position = position;
		objMgr.AddComponent<RigidBody>(doorObj).SetMass(0);
		objMgr.AddCollider(doorObj, true);

		return &door;
	}

	void CaptainStealth::SpawnKey(ObjectManager& objMgr, Door* door, Sprite image, AEVec2 position)
	{
		GameObject* key = objMgr.NewGameObject();
		objMgr.AddImage(key, image);
		key->transform.scale = { 0.5f, 0.5f };

		objMgr.AddComponent<Key>(key, door);
		key->transform.position = position;
		objMgr.AddCollider(key, true).isTrigger = true;
	}

	void CaptainStealth::SpawnPlayer(ObjectManager& objMgr, GameObject*& player, Sprite playerImage)
	{
		player = objMgr.NewGameObject();
		player->name = "Player";
		player->transform.scale = { 0.7f, 0.7f };

		objMgr.AddImage(player, playerImage);

		objMgr.AddComponent<CameraComponent>(player);

		objMgr.AddCollider(player, false);
		objMgr.AddComponent<PrimaryMovementController>(player);

		objMgr.AddComponent<PlayerScript>(player);
	}

	void CaptainStealth::SpawnClient(ObjectManager& objMgr, GameObject*& client, Sprite clientImage)
	{
		client = objMgr.NewGameObject();
		client->name = "Client";
		client->transform.scale = { 0.7f, 0.7f };

		objMgr.AddImage(client, clientImage);
		objMgr.AddCollider(client, false);
		objMgr.AddComponent<PrimaryMovementController>(client);
	}

}

