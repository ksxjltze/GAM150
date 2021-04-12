/******************************************************************************/
/*!
\title		Captain Stealth
\file		PlayerScript.cpp
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Player script.
			Responsible for Player mechanics such as Stealth
			as well as controlling the win and lose conditions for the game.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/


#include "PlayerScript.h"
#include "MessageBus.h"
#include "Collider.h"
#include "ObjectManager.h"
#include "CollisionEvent.h"
#include "SoundEvent.h"
#include "constants.h"
#include "globals.h"
#include "Text.h"
#include <iomanip>
#include <sstream>
#include "MovementManager.h"

/*!*************************************************************************
 * \brief
 * Script constructor.
 * Attaches the script to a game object
 * \param obj
 * GameObject to attach to.
***************************************************************************/
StarBangBang::PlayerScript::PlayerScript(GameObject* obj) : Script(obj)
{
	client = nullptr;
	rb_controller = nullptr;
	gameover = false;
	playerEscaped = false;
	clientEscaped = false;
	stealth = nullptr;
	text = nullptr;
	gameOverTimer = 0.f;
}

/*!*************************************************************************
 * \brief
 * Start.
 * \return
 * void
***************************************************************************/
void StarBangBang::PlayerScript::Start()
{

	rb_controller = gameObject->GetComponent<PrimaryMovementController>();

	stealth = &objMgr->AddComponent<StealthWalk>(gameObject);
	stealth->Start();

	text = &objMgr->AddComponent<Text>(gameObject, "", fontId2);
	text->SetOffset({ 0, -30 });

	client = objMgr->Find("Client");

	assert(client);
	assert(rb_controller);

}

/*!*************************************************************************
 * \brief
 * Determines if the player is invisible.
 * \return
 * False if player is visible, true otherwise.
***************************************************************************/
bool StarBangBang::PlayerScript::isInvisible()
{
	return stealth->IsInvisible();
}

/*!*************************************************************************
 * \brief
 * Resets the game over condition.
 * \return
 * void
***************************************************************************/
void StarBangBang::PlayerScript::Debug_Reset()
{
	gameover = false;
}

/*!*************************************************************************
 * \brief
 * Listener callback. Invoked when an event is received from the Message Bus.
 * Listens for events: CAUGHT_BY_CAMERA, GAME_OVER, DETECTED,
 *					   PLAYER_COLLISION and COLLISION.
 * \param e Event data.
***************************************************************************/
void StarBangBang::PlayerScript::onNotify(Event e)
{
	if (e.id == EventId::CAUGHT_BY_CAMERA)
	{
		detected = true;
	}

	if (e.id == EventId::GAME_OVER)
	{
		GameObject* detectedObj = std::any_cast<GameObject*>(e.context);
		if (detectedObj->active)
			gameover = true;
	}

	if (e.id == EventId::DETECTED)
	{
		if (!detected)
			SoundEvent(std::string(SFX::DETECTED)).SendEvent();

		GameObject* detectedObj = std::any_cast<GameObject*>(e.context);
		if (detectedObj->active)
		{
			detected = true;

			if (god)
				return;

			// Don't allow player to move when detected
			gameObject->GetComponent<PrimaryMovementController>()->SetActive(false);
			client->GetComponent<PrimaryMovementController>()->SetActive(false);
		}
	}

	if (e.id == EventId::PLAYER_COLLISION)
	{
		CollisionEvent data = std::any_cast<CollisionEvent>(e.context);
		if (data.second->gameObject->name == "Guard")
		{
			gameover = true;
		}
	}

	if (e.id == EventId::COLLISION)
	{
		CollisionEvent data = std::any_cast<CollisionEvent>(e.context);
		GameObject* obj = data.second->gameObject;

		if (data.first->gameObject->name == "EXIT")
		{
			if (obj->name == "Player")
			{
				objMgr->Find("MovementManager")->GetComponent<MovementManager>()->RemoveController(gameObject);
				BoxCollider* collider = gameObject->GetComponent<BoxCollider>();
				collider->isTrigger = true;
				collider->isStatic = true;
				playerEscaped = true;
			}
			else if (obj->name == "Client")
			{
				objMgr->Find("MovementManager")->GetComponent<MovementManager>()->RemoveController(client);
				BoxCollider* collider = client->GetComponent<BoxCollider>();
				collider->isTrigger = true;
				collider->isStatic = true;
				clientEscaped = true;
			}
		}
		else if (data.first->gameObject->name == "Vent")
		{
			if (obj->name == "Player" || obj->name == "Client")
			{
				if (obj->name == "Player")
					playerHidden = true;
				else
					clientHidden = true;

				obj->visible = false;
				obj->GetComponent<BoxCollider>()->isTrigger = true;
			}
		}
	}
}

/*!*************************************************************************
 * \brief
 * Updates the player's cooldown and ability timers.
 * Checks if the game is over or if the player has won.
 * \return
 * void
***************************************************************************/
void StarBangBang::PlayerScript::Update()
{	
	if (detected)
	{
		gameOverTimer += g_dt;
		if (gameOverTimer >= 10.f)
			gameover = true;
	}

	float timer = stealth->GetTimer();
	if (timer >= EPSILON)
	{
		std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << timer;
		std::string s = stream.str();
		text->SetText(s);
	}
	else
	{
		text->SetText("");
	}

	if (playerHidden)
		playerHidden = false;
	else
	{
		gameObject->visible = true;
		gameObject->GetComponent<BoxCollider>()->isTrigger = false;
	}

	if (clientHidden)
		clientHidden = false;
	else
	{
		client->visible = true;
		client->GetComponent<BoxCollider>()->isTrigger = false;
	}
}

/*!*************************************************************************
 * \brief
 * Determines if the game is over.
 * \return
 * True if the conditions for game over are met,
 * false otherwise.
***************************************************************************/
bool StarBangBang::PlayerScript::isGameOver()
{
	return gameover;
}

/*!*************************************************************************
 * \brief
 * Determines if the game is won.
 * \return
 * True if the conditions for winning are met,
 * false otherwise.
***************************************************************************/
bool StarBangBang::PlayerScript::isWin()
{
	if (playerEscaped && clientEscaped)
		return true;
	else
		return false;
}
