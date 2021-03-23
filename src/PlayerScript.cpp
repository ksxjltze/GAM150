#include "PlayerScript.h"
#include "MessageBus.h"
#include "Collider.h"

StarBangBang::PlayerScript::PlayerScript(GameObject* obj) : Script(obj)
{
	client = nullptr;
	rb_controller = nullptr;
	range = 30.0f;
	gameover = false;
	playerEscaped = false;
	clientEscaped = false;
}
void StarBangBang::PlayerScript::Start()
{

	rb_controller = gameObject->GetComponent<PrimaryMovementController>();
	

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

	if (e.id == EventId::COLLISION)
	{
		using colPair = std::pair<Collider*, Collider*>;
		colPair pair = std::any_cast<colPair>(e.context);

		if (pair.first->gameObject->name == "EXIT" && pair.second->gameObject->name == "Player")
		{
			printf("PLAYER ESCAPED\n");
			pair.second->gameObject->active = false;
			playerEscaped = true;
		}
		if (pair.first->gameObject->name == "EXIT" && pair.second->gameObject->name == "Client")
		{
			pair.second->gameObject->active = false;
			clientEscaped = true;
		}

	}
}

void StarBangBang::PlayerScript::Update()
{
	
	AEVec2 myPos = gameObject->transform.position;
	AEVec2 clientPos = client->GetPos();
	float real_sqrDis = AEVec2SquareDistance(&myPos, &clientPos);

	if (real_sqrDis > range )
	{
		rb_controller->active = false;
	}
	else
	{
		rb_controller->active = true;
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
