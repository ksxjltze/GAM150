/******************************************************************************/
/*!
\title		Captain Stealth
\file		CaptainStealth.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Captain Stealth scene.
			Currently not in use (as a scene).

			Contains functions for spawning gameplay elements.
			E.g. Player, Client, Key, Door

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "State.h"

#include "MovementManager.h"
#include "MessageBus.h"
#include "PlayerScript.h"
#include "CameraComponent.h"
#include "PrimaryMovementController.h"
#include "Text.h"
#include "Door.h"

namespace StarBangBang
{
	class CaptainStealth : public Scene
	{
	public:
		CaptainStealth(int id, GameStateManager& gsm);
		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();

		static void SpawnPlayer(ObjectManager& objMgr, GameObject*& player,Sprite image);
		static void SpawnClient(ObjectManager& objMgr, GameObject*& client, Sprite image);
		static Door* SpawnDoor(ObjectManager& objMgr, Sprite image, AEVec2 position);
		static void SpawnKey(ObjectManager& objMgr, Door* door, Sprite image, AEVec2 position);

	private:
		GameObject* player;
	};

}