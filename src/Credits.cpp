/******************************************************************************/
/*!
\title		Captain Stealth
\file		Credits.cpp
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Credits scene.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#include "Credits.h"
#include "Text.h"
#include "globals.h"
#include "CameraComponent.h"

namespace StarBangBang
{
	const static float CAMERA_SPEED = 30.0f;
	const static float CREDITS_SPEED_UP_FACTOR = 10.0f;
	const static float END_OFFSET = 50.0f;
	static Sprite logoSprite;

	void Credits::NewTextObject(AEVec2 position, const std::string& s, float scale, Color c)
	{
		objectManager.AddComponent<Text>(objectManager.NewGameObject(), s, fontId2, c, scale).gameObject->transform.position = position;
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
		float role_spacing = -40.0f;
		float section_spacing = -60.0f;

		AEVec2 pos = { 0.0f, 210.0f };

		GRAPHICS::SetBackgroundColor(Black);

		cameraObject = objectManager.NewGameObject();
		objectManager.AddComponent<CameraComponent>(cameraObject);
		ImageComponent* logoImg = objectManager.AddImage(objectManager.NewGameObject(), logoSprite);
		logoImg->gameObject->transform.position.y = 100.0f;
		logoImg->gameObject->transform.scale.x = 6.0f;
		logoImg->gameObject->transform.scale.y = 1.5f;

		end = objectManager.NewGameObject();
		cameraObject->transform.scale = { EPSILON, EPSILON };
		objectManager.AddImage(cameraObject, logoSprite);

		NewTextObject(pos, "StarBangBang", 1.5f, Yellow);
		NewTextObject({ pos.x, pos.y += spacing }, "Presents", 0.8f);

		pos = { 0, 20 };

		Color roleColor = Cyan;

		NewTextObject(pos, "Producer", 0.9f, roleColor);
		NewTextObject({pos.x, pos.y += spacing}, "Ho Yi Guan", 1.0f);

		NewTextObject({ pos.x, pos.y += role_spacing }, "Technical Director", 0.9f, roleColor);
		NewTextObject({ pos.x, pos.y += spacing}, "Lee Jia Keat", 1.0f);

		NewTextObject({ pos.x, pos.y += role_spacing }, "Design Lead", 0.9f, roleColor);
		NewTextObject({ pos.x, pos.y += spacing }, "Rayner Liew", 1.0f);

		NewTextObject({ pos.x, pos.y += role_spacing }, "Testing Lead", 0.9f, roleColor);
		NewTextObject({ pos.x, pos.y += spacing }, "Sim Chin Hin", 1.0f);

		NewTextObject({ pos.x, pos.y += section_spacing }, "Lecturers", 0.9f, roleColor);
		NewTextObject({ pos.x, pos.y += spacing }, "Cheng Ding Xiang", 1.0f);
		NewTextObject({ pos.x, pos.y += spacing }, "Tomas Arce-Gil", 1.0f);
		NewTextObject({ pos.x, pos.y += spacing }, "Wong Han Feng, Gerald", 1.0f);

		NewTextObject({ pos.x, pos.y += section_spacing }, "Created At", 0.9f, roleColor);
		NewTextObject({ pos.x, pos.y += spacing }, "DigiPen Institute of Technology Singapore", 0.9f);

		NewTextObject({ pos.x, pos.y += role_spacing }, "PRESIDENT", 1.0f, roleColor);
		NewTextObject({ pos.x, pos.y += spacing }, "CLAUDE COMAIR", 0.9f);

		NewTextObject({ pos.x, pos.y += section_spacing }, "EXECUTIVES", 1.0f, roleColor);
		NewTextObject({ pos.x, pos.y += spacing }, "JASON CHU", 0.6f);
		NewTextObject({ pos.x, pos.y += spacing }, "SAMIR ABOU SAMRA", 0.6f);
		NewTextObject({ pos.x, pos.y += spacing }, "MICHELE COMAIR", 0.6f);
		NewTextObject({ pos.x, pos.y += spacing }, "ANGELA KUGLER", 0.6f);
		NewTextObject({ pos.x, pos.y += spacing }, "ERIK MOHRMANN", 0.6f);
		NewTextObject({ pos.x, pos.y += spacing }, "BENJAMIN ELLINGER", 0.6f);
		NewTextObject({ pos.x, pos.y += spacing }, "MELVIN GONSALVEZ", 0.6f);

		spacing += 20;
		NewTextObject({ pos.x, pos.y += section_spacing }, "www.digipen.edu", 0.8f);
		NewTextObject({ pos.x, pos.y += section_spacing / 2 }, "All content Copyright 2021 DigiPen Institute of Technology Singapore.", 0.7f);
		NewTextObject({ pos.x, pos.y += section_spacing / 2 }, "All Rights Reserved", 0.8f);

		NewTextObject({ pos.x, pos.y += section_spacing }, "FMOD Sound System Copyright FireLight Technologies Pty Ltd (1998 - 2021)", 0.8f);

		cameraObject->transform.position.y = 100.0f;
		end->transform.position = { pos.x, pos.y };
	}

	void StarBangBang::Credits::Update()
	{
		float speed = CAMERA_SPEED;
		if (AEInputCheckCurr(AEVK_SPACE))
		{
			speed *= CREDITS_SPEED_UP_FACTOR;
		}

		if (AEInputCheckTriggered(AEVK_ESCAPE) || AEInputCheckTriggered(AEVK_RETURN))
		{
			gameStateManager.SetNextGameState(MAIN_MENU);
			return;
		}

		cameraObject->transform.position.y -= speed * g_dt;

		if (cameraObject->GetPos().y < end->GetPos().y - AEGetWindowHeight() / 2)
		{
			gameStateManager.SetNextGameState(MAIN_MENU);
			return;
		}

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

