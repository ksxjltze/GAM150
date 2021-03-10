#include "EngineProof.h"
#include "CameraComponent.h"
#include "constants.h"
#include "globals.h"
#include "SecondaryMovementController.h"

namespace StarBangBang
{
	static Sprite sprite;
	StarBangBang::EngineProof::EngineProof(int id, GameStateManager& manager) : Scene(id, manager)
	{

	}

	void StarBangBang::EngineProof::Load()
	{
		sprite = graphicsManager.CreateSprite(RESOURCES::SECURITYGUARD_F1_PATH);
	}

	void StarBangBang::EngineProof::Init()
	{
		GRAPHICS::SetBackgroundColor(LightGreen());
		GameObject* camera = objectManager.NewGameObject();
		objectManager.AddComponent<CameraComponent>(camera);
	}

	void StarBangBang::EngineProof::Update()
	{
		if (AEInputCheckCurr(AEVK_S))
		{
			SpawnObject();
		}

		if (AEInputCheckTriggered(AEVK_SPACE))
		{
			gameStateManager.SetNextGameState(SceneID::DEMO);
			//gameStateManager.SetNextGameState(SceneID::SAMPLE);
		}
		Scene::Update();
		
		static float spawnTimer = 0;
		if ((spawnTimer -= static_cast<float>(g_dt)) <= 0)
		{
			spawnTimer = 0.5f;
			SpawnObject();
		}

	}

	void StarBangBang::EngineProof::Draw()
	{
		Scene::Draw();
	}

	void StarBangBang::EngineProof::Free()
	{
		Scene::Free();
	}

	void StarBangBang::EngineProof::Unload()
	{
		Scene::Unload();
	}

	void EngineProof::SpawnObject()
	{
		GameObject* obj = objectManager.NewGameObject();
		objectManager.AddComponent<ImageComponent>(obj, sprite);

		obj->transform.position = 
		{ AEGetWindowWidth()  * AERandFloat() - AEGetWindowWidth() / 2,
		   AEGetWindowHeight() * AERandFloat() - AEGetWindowHeight() / 2 };

		objectManager.AddComponent<SecondaryMovementController>(obj).Start();
	}

}
