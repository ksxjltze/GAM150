#include "PlayerScript.h"
#include "MessageBus.h"
#include "Collider.h"

StarBangBang::PlayerScript::PlayerScript(GameObject* obj) : Script(obj)
{

}
void StarBangBang::PlayerScript::Start()
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
		using colPair = std::pair<Collider*, Collider*>;
		colPair pair = std::any_cast<colPair>(e.context);

		if (pair.first->gameObject->name == "EXIT" && pair.second->gameObject->name == "Player")
		{
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
