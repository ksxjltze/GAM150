#include "Credits.h"
#include "Text.h"
#include "globals.h"
#include "CameraComponent.h"

namespace StarBangBang
{
	const static float CAMERA_SPEED = 30.0f;
	static Sprite logoSprite;

	void Credits::NewTextObject(AEVec2 position, const std::string& s, float scale)
	{
		objectManager.AddComponent<Text>(objectManager.NewGameObject(), s, fontId2, scale).gameObject->transform.position = position;
	}

	StarBangBang::Credits::Credits(int id, GameStateManager& gsm) : Scene(id, gsm)
	{

	}

	void StarBangBang::Credits::Load()
	{
		logoSprite = graphicsManager.CreateSprite(RESOURCES::LOGO_PATH);
	}

	void StarBangBang::Credits::Init()
	{
		float spacing = -35.0f;
		float role_spacing = -55.0f;
		float section_spacing = -100.0f;

		AEVec2 pos = { 0.0f, 210.0f };

		GRAPHICS::SetBackgroundColor(Black);

		cameraObject = objectManager.NewGameObject();
		objectManager.AddComponent<CameraComponent>(cameraObject);
		ImageComponent* logoImg = objectManager.AddImage(objectManager.NewGameObject(), logoSprite);
		logoImg->gameObject->transform.position.y = 100.0f;
		logoImg->gameObject->transform.scale.x = 6.0f;
		logoImg->gameObject->transform.scale.y = 1.5f;

		NewTextObject(pos, "StarBangBang", 1.0f);
		NewTextObject({ pos.x, pos.y += spacing }, "Presents", 0.8f);

		pos = { 0, 0 };

		NewTextObject(pos, "Producer", 0.5f);
		NewTextObject({pos.x, pos.y += spacing}, "Ho Yi Guan", 1.0f);

		NewTextObject({ pos.x, pos.y += role_spacing }, "Technical Director", 0.5f);
		NewTextObject({ pos.x, pos.y += spacing}, "Lee Jia Keat", 1.0f);

		NewTextObject({ pos.x, pos.y += role_spacing }, "Design Lead", 0.5f);
		NewTextObject({ pos.x, pos.y += spacing }, "Rayner Liew", 1.0f);

		NewTextObject({ pos.x, pos.y += role_spacing }, "Testing Lead", 0.5f);
		NewTextObject({ pos.x, pos.y += spacing }, "Sim Chin Hin", 1.0f);

		NewTextObject({ pos.x, pos.y += section_spacing }, "Lecturers", 0.5f);
		NewTextObject({ pos.x, pos.y += spacing }, "Cheng Ding Xiang", 1.0f);
		NewTextObject({ pos.x, pos.y += spacing }, "Tomas Arce-Gil", 1.0f);
		NewTextObject({ pos.x, pos.y += spacing }, "Wong Han Feng, Gerald", 1.0f);

		cameraObject->transform.position.y = 100.0f;
	}

	void StarBangBang::Credits::Update()
	{
		cameraObject->transform.position.y -= CAMERA_SPEED * g_dt;
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

