#include "PlayerScript.h"
#include "MessageBus.h"
#include "Collider.h"
#include "ObjectManager.h"
#include "CollisionEvent.h"

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
	client = objMgr->Find("Client");

	assert(client);
	assert(rb_controller);
	range *= range;

}
void StarBangBang::PlayerScript::onNotify(Event e)
{
	if (e.id == EventId::DETECTED)
	{
		GameObject* detectedObj = std::any_cast<GameObject*>(e.context);
		if (detectedObj->active)
			gameover = true;
	}

	if (e.id == EventId::PLAYER_COLLISION)
	{
		CollisionEvent data = std::any_cast<CollisionEvent>(e.context);
		if (data.colliderPair.second->gameObject->name == "Guard")
		{
			gameover = true;
		}
	}

	if (e.id == EventId::COLLISION)
	{
		CollisionEvent data = std::any_cast<CollisionEvent>(e.context);

		if (data.colliderPair.first->gameObject->name == "EXIT" && data.colliderPair.second->gameObject->name == "Player")
		{
			printf("PLAYER ESCAPED\n");
			data.colliderPair.second->gameObject->active = false;
			playerEscaped = true;
		}
		if (data.colliderPair.first->gameObject->name == "EXIT" && data.colliderPair.second->gameObject->name == "Client")
		{
			data.colliderPair.second->gameObject->active = false;
			clientEscaped = true;
		}

	}
}

void StarBangBang::PlayerScript::Update()
{
	
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
