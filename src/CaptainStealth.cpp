#include "CaptainStealth.h"
#include "globals.h"
#include "constants.h"

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

	void CaptainStealth::SpawnDoor(ObjectManager& objMgr, Sprite image, AEVec2 position)
	{
		GameObject* doorObj = objMgr.NewGameObject();
		objMgr.AddImage(doorObj, image);
		doorObj->transform.position = position;

		ComputerListener& listener = objMgr.AddComponent<ComputerListener>(doorObj);
		MessageBus::RegisterListener(&listener);
	}

	void CaptainStealth::SpawnPlayer(ObjectManager& objMgr, GameObject*& player, Sprite playerImage)
	{
		player = objMgr.NewGameObject();
		player->name = "Player";
		player->SetPos({ 250, 800 });
		player->transform.scale = { 0.7f, 0.7f };

		DetectionListener* listener = &objMgr.AddComponent<DetectionListener>(player);
		MessageBus::RegisterListener(listener);
		objMgr.AddImage(player, playerImage);

		objMgr.AddComponent<Text>(player).fontID = StarBangBang::fontId;
		objMgr.AddComponent<CameraComponent>(player);

		objMgr.AddCollider(player, false);
		objMgr.AddComponent<PrimaryMovementController>(player);

		Listener* l = &objMgr.AddComponent<PlayerScript>(player);
		MessageBus::RegisterListener(l);
	}

	void CaptainStealth::SpawnClient(ObjectManager& objMgr, GameObject*& client, Sprite clientImage)
	{
		client = objMgr.NewGameObject();
		client->SetPos({ 250, 950 });
		client->transform.scale = { 0.7f, 0.7f };

		objMgr.AddImage(client, clientImage);
		objMgr.AddCollider(client, false);
		objMgr.AddComponent<PrimaryMovementController>(client);
	}

}

