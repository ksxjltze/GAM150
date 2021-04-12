/******************************************************************************/
/*!
\title		Captain Stealth
\file		CaptainStealth.cpp
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Captain Stealth scene.
			Currently not in use (as a scene).

			Contains functions for spawning gameplay elements.
			E.g. Player, Client, Key, Door

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/

#include "CaptainStealth.h"
#include "globals.h"
#include "constants.h"
#include "Door.h"

namespace StarBangBang
{
	static Sprite playerSprite;

	/*!*************************************************************************
	 * \brief
	 * Scene constructor.
	 * \param id
	 * Id of the scene
	 * \param gsm
	 * Reference to the game state manager.
	***************************************************************************/
	StarBangBang::CaptainStealth::CaptainStealth(int id, GameStateManager& gsm) : Scene(id, gsm), player{ nullptr }
	{

	}

	/*!*************************************************************************
	 * \brief
	 * Load function. Called once when the scene starts.
	 * \return void
	***************************************************************************/
	void StarBangBang::CaptainStealth::Load()
	{
		playerSprite = graphicsManager.CreateSprite(RESOURCES::SPRITE_PLAYER_PATH);
	}

	/*!*************************************************************************
	 * \brief
	 * Init function. Called once when the scene starts.
	 * \return void
	***************************************************************************/
	void StarBangBang::CaptainStealth::Init()
	{

	}

	/*!*************************************************************************
	 * \brief
	 * Update function.
	 * \return void
	***************************************************************************/
	void StarBangBang::CaptainStealth::Update()
	{
		Scene::Update();
	}

	/*!*************************************************************************
	 * \brief
	 * Draw function
	 * \return void
	***************************************************************************/
	void StarBangBang::CaptainStealth::Draw()
	{
		Scene::Draw();
	}

	/*!*************************************************************************
	 * \brief
	 * Free function.
	 * \return void
	***************************************************************************/
	void StarBangBang::CaptainStealth::Free()
	{
		Scene::Free();
	}

	/*!*************************************************************************
	 * \brief
	 * Unload function.
	 * \return void
	***************************************************************************/
	void StarBangBang::CaptainStealth::Unload()
	{
		Scene::Unload();
	}

	/*!*************************************************************************
	 * \brief
	 * Spawns a door object.
	 * \param objMgr
	 * Reference to the object manager.
	 * \param image
	 * The door's sprite
	 * \param position
	 * Position to spawn the door at.
	 * \return
	***************************************************************************/
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

	/*!*************************************************************************
	 * \brief
	 * Spawns a key object.
	 * \param objMgr
	 * Reference to the object manager.
	 * \param door
	 * Pointer to the door object to link to.
	 * \param image
	 * The key's sprite.
	 * \param position
	 * Position to spawn the key at.
	***************************************************************************/
	void CaptainStealth::SpawnKey(ObjectManager& objMgr, Door* door, Sprite image, AEVec2 position)
	{
		GameObject* key = objMgr.NewGameObject();
		objMgr.AddImage(key, image);
		key->transform.scale = { 0.5f, 0.5f };

		objMgr.AddComponent<Key>(key, door);
		key->transform.position = position;
		objMgr.AddCollider(key, true).isTrigger = true;
	}

	/*!*************************************************************************
	 * \brief
	 * Spawns a player game object.
	 * \param objMgr
	 * Reference to the object manager.
	 * \param player
	 * Reference to the pointer to the player in the scene.
	 * \param image
	 * The player's sprite
	***************************************************************************/
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

	/*!*************************************************************************
	 * \brief
	 * Spawns a client game object.
	 * \param objMgr
	 * Reference to the object manager.
	 * \param client
	 * Reference to the pointer to the client in the scene.
	 * \param image
	 * The client's sprite
	***************************************************************************/
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

