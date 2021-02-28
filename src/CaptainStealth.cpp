#include "CaptainStealth.h"
#include "constants.h"
#include "Player.h"

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
		player = objectManager.NewGameObject();
		objectManager.AddComponent<Player>(player);
		objectManager.AddImage(player, playerSprite);
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

}

