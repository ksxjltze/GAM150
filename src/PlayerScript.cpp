#include "PlayerScript.h"
#include "MessageBus.h"
#include "Collider.h"

StarBangBang::PlayerScript::PlayerScript(GameObject* obj) : Script(obj)
{

}

void StarBangBang::PlayerScript::onNotify(Event e)
{
	if (e.id == EventId::DETECTED)
	{
		gameover = true;
	}

	if (e.id == EventId::COLLISION)
	{
		using colPair = std::pair<Collider*, Collider*>;
		colPair pair = std::any_cast<colPair>(e.context);

		if (pair.first->gameObject->name == "EXIT" && pair.second->gameObject->name == "Player")
			win = true;
	}
}

bool StarBangBang::PlayerScript::isGameOver()
{
	return gameover;
}

bool StarBangBang::PlayerScript::isWin()
{
	return win;
}
