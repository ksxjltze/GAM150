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
	range = 500.0f;
	gameover = false;
	playerEscaped = false;
	clientEscaped = false;
	stealth = nullptr;
}
void StarBangBang::PlayerScript::Start()
{

	rb_controller = gameObject->GetComponent<PrimaryMovementController>();

	stealth = &objMgr->AddComponent<StealthWalk>(gameObject);
	stealth->Start();

	text = &objMgr->AddComponent<Text>(gameObject, "", fontId2);
	text->SetOffset({ 0, -30 });

	client = objMgr->Find("Client");
	range *= range;

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

		if (data.first->gameObject->name == "EXIT" && data.second->gameObject->name == "Player")
		{
			printf("PLAYER ESCAPED\n");
			data.second->active = false;
			playerEscaped = true;
		}
		if (data.first->gameObject->name == "EXIT" && data.second->gameObject->name == "Client")
		{
			data.second->active = false;
			clientEscaped = true;
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

	/*AEVec2 myPos = gameObject->transform.position;
	AEVec2 clientPos = client->GetPos();
	float real_sqrDis = AEVec2SquareDistance(&myPos, &clientPos);*/

	/*if (myPos.x > AEGfxGetWinMaxX() || myPos.x < AEGfxGetWinMinX()
		|| myPos.y > AEGfxGetWinMaxY() || myPos.y < AEGfxGetWinMinY())
	{
		rb_controller->active = false;
	}*/
		
	/*if (real_sqrDis > range )
	{
		rb_controller->active = false;
	}*/


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
