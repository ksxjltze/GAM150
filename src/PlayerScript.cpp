#include "PlayerScript.h"
#include "MessageBus.h"
#include "Collider.h"
#include "ObjectManager.h"
#include "CollisionEvent.h"
#include "SoundEvent.h"
#include "constants.h"
#include "globals.h"

StarBangBang::PlayerScript::PlayerScript(GameObject* obj) : Script(obj)
{
	client = nullptr;
	rb_controller = nullptr;
	range = 500.0f;
	gameover = false;
	playerEscaped = false;
	clientEscaped = false;
}
void StarBangBang::PlayerScript::Start()
{

	rb_controller = gameObject->GetComponent<PrimaryMovementController>();
	image = gameObject->GetComponent<ImageComponent>();
	client = objMgr->Find("Client");

	assert(client);
	assert(rb_controller);
	range *= range;

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

	if (AEInputCheckTriggered(AEVK_Q) && cooldown <= EPSILON)
	{
		invisible = true;
		image->SetTransparency(0.4f);
		timer = 10.0f;
		cooldown = 10.0f;
	}

	if (timer > EPSILON)
	{
		timer -= g_dt;
		if (timer <= EPSILON)
		{
			invisible = false;
			image->SetTransparency(1.0f);
		}
	}
	else if (cooldown > EPSILON)
	{
		cooldown -= g_dt;
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
