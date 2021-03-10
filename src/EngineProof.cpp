#include "EngineProof.h"
#include "CameraComponent.h"
#include "constants.h"

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
		GRAPHICS::SetBackgroundColor(Black());
		GameObject* camera = objectManager.NewGameObject();
		objectManager.AddComponent<CameraComponent>(camera);
	}

	void StarBangBang::EngineProof::Update()
	{
		if (AEInputCheckTriggered(VK_SPACE))
		{
			SpawnObject();
		}
		Scene::Update();
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
	}

}
