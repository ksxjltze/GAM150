/******************************************************************************/
/*!
\title		Captain Stealth
\file		Key.cpp
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Key script.
			Opens a linked door when enough keys have been collected.
			Keys are collected on collision with the client character.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#include "Key.h"
#include "CollisionEvent.h"
#include "Door.h"
#include "globals.h"
#include "SoundEvent.h"

namespace StarBangBang
{
	/*!*************************************************************************
	 * \brief
	 * Script Constructor.
	 * Attaches the script to a game object
	 * \param obj
	 * GameObject to attach to.
	 * \param door
	 * Door to link to.
	***************************************************************************/
	Key::Key(GameObject* obj, Door* door) : Script(obj), door{ door }, collected{ false }
	{
		scale = gameObject->transform.scale.x;
	}

	/*!*************************************************************************
	 * \brief
	 * Accessor.
	 * \return
	 * True if the key is collected, false otherwise.
	***************************************************************************/
	bool Key::isCollected()
	{
		return collected;
	}

	/*!*************************************************************************
	 * \brief
	 * Sends a key pickup event.
	 * Invoked when the correct collision event is received.
	 * \return void
	***************************************************************************/
	void Key::Pickup()
	{
		SoundEvent(SFX::KEY_PICKUP).SendEvent();
		gameObject->active = false;
		collected = true;
	}

	/*!*************************************************************************
	 * \brief
	 * Event callback.
	 * Listens for COLLISION events that involve the
	 * client character and the current object.
	 * \param e
	 * Event data
	 * \return
	 * void
	***************************************************************************/
	void Key::onNotify(Event e)
	{
		if (e.id == EventId::COLLISION)
		{
			CollisionEvent colEvent = std::any_cast<CollisionEvent>(e.context);
			if (colEvent.second->gameObject != gameObject)
				return;

			if (colEvent.first->gameObject->name == "Client")
				Pickup();

		}
	}

	/*!*************************************************************************
	 * \brief
	 * Start function. Called once at the start of the scene.
	***************************************************************************/
	void Key::Start()
	{
		door->AddKey(this);
		collected = false;
	}

	/*!*************************************************************************
	 * \brief
	 * Update function. Called once per frame.
	***************************************************************************/
	void Key::Update()
	{
		if (!flip)
			gameObject->transform.scale.x -= g_dt;
		else
			gameObject->transform.scale.x += g_dt;

		if (gameObject->transform.scale.x < -scale)
			flip = true;
		else if (gameObject->transform.scale.x > scale)
			flip = false;
	}
}