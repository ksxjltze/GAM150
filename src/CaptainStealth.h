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

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
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
		/*!*************************************************************************
		 * \brief 
		 * Scene constructor.
		 * \param id
		 * Id of the scene
		 * \param gsm
		 * Reference to the game state manager.
		***************************************************************************/
		CaptainStealth(int id, GameStateManager& gsm);

		/*!*************************************************************************
		 * \brief 
		 * Load function. Called once when the scene starts.
		 * \return void
		***************************************************************************/
		void Load();

		/*!*************************************************************************
		 * \brief
		 * Init function. Called once when the scene starts.
		 * \return void
		***************************************************************************/
		void Init();

		/*!*************************************************************************
		 * \brief
		 * Update function.
		 * \return void
		***************************************************************************/
		void Update();

		/*!*************************************************************************
		 * \brief
		 * Draw function
		 * \return void
		***************************************************************************/
		void Draw();

		/*!*************************************************************************
		 * \brief
		 * Free function.
		 * \return void
		***************************************************************************/
		void Free();

		/*!*************************************************************************
		 * \brief
		 * Unload function.
		 * \return void
		***************************************************************************/
		void Unload();

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
		static void SpawnPlayer(ObjectManager& objMgr, GameObject*& player,Sprite image);

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
		static void SpawnClient(ObjectManager& objMgr, GameObject*& client, Sprite image);

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
		static Door* SpawnDoor(ObjectManager& objMgr, Sprite image, AEVec2 position);

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
		static void SpawnKey(ObjectManager& objMgr, Door* door, Sprite image, AEVec2 position);

	private:
		GameObject* player;
	};

}