#include "PlayerScript.h"
#include "CollisionEvent.h"

StarBangBang::PlayerScript::PlayerScript(GameObject* obj) : Script(obj)
{

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
