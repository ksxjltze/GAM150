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

StarBangBang::PlayerScript::PlayerScript(GameObject* obj) : Script(obj)
{
	client = nullptr;
	rb_controller = nullptr;
	gameover = false;
	playerEscaped = false;
	clientEscaped = false;
	stealth = nullptr;
	text = nullptr;
}
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

bool StarBangBang::PlayerScript::isInvisible()
{
	return stealth->IsInvisible();
}

void StarBangBang::PlayerScript::Debug_Reset()
{
	gameover = false;
}

void StarBangBang::PlayerScript::onNotify(Event e)
{
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
				data.second->active = false;
				playerEscaped = true;
			}
			else if (obj->name == "Client")
			{
				data.second->active = false;
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

void StarBangBang::PlayerScript::Update()
{	
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

bool StarBangBang::PlayerScript::isGameOver()
{
	return gameover;
}

bool StarBangBang::PlayerScript::isWin()
{
	if (playerEscaped && clientEscaped)
		return true;
	else
		return false;
}
