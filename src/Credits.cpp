#include "Credits.h"
#include "Text.h"
#include "globals.h"
#include "CameraComponent.h"

namespace StarBangBang
{
	const static float CAMERA_SPEED = 20.0f;
	static Sprite logoSprite;

	StarBangBang::Credits::Credits(int id, GameStateManager& gsm) : Scene(id, gsm)
	{

	}

	void StarBangBang::Credits::Load()
	{
		logoSprite = graphicsManager.CreateSprite(RESOURCES::LOGO_PATH);
	}

	void StarBangBang::Credits::Init()
	{
		GRAPHICS::SetBackgroundColor(Black);

		cameraObject = objectManager.NewGameObject();
		objectManager.AddComponent<CameraComponent>(cameraObject);
		objectManager.AddImage(objectManager.NewGameObject(), logoSprite)->gameObject->transform.position.y = 100.0f;

		objectManager.AddComponent<Text>(objectManager.NewGameObject(), "Test", fontId2);
	}

	void StarBangBang::Credits::Update()
	{
		//cameraObject->transform.position.y -= CAMERA_SPEED * g_dt;
		Scene::Update();
	}

	void StarBangBang::Credits::Draw()
	{
		Scene::Draw();
	}

	void StarBangBang::Credits::Free()
	{
		Scene::Free();
	}

	void StarBangBang::Credits::Unload()
	{
		Scene::Unload();
	}

}

