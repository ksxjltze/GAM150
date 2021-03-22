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

	void CaptainStealth::SpawnPlayer(ObjectManager& objMgr, GameObject*& player, Sprite playerImage)
	{
		player = objMgr.NewGameObject();
		player->SetPos({ 250, 800 });
		player->transform.scale = { 0.7f, 0.7f };

		DetectionListener* listener = &objMgr.AddComponent<DetectionListener>(player);
		MessageBus::RegisterListener(listener);
		objMgr.AddImage(player, playerImage);
		objMgr.AddComponent<Text>(player).fontID = StarBangBang::fontId;
		objMgr.AddComponent<CameraComponent>(player);
		objMgr.AddComponent<RigidBody>(player);
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
		objMgr.AddComponent<RigidBody>(client);
		objMgr.AddCollider(client, false).isTrigger = true;
		objMgr.AddComponent<PrimaryMovementController>(client);
	}

}

