#include "PlayerScript.h"
#include "MessageBus.h"

StarBangBang::PlayerScript::PlayerScript(GameObject* obj) : Script(obj)
{

}

void StarBangBang::PlayerScript::onNotify(Event e)
{
	if (e.id == EventId::DETECTED)
	{
		gameover = true;
	}
}

bool StarBangBang::PlayerScript::isGameOver()
{
	return gameover;
}
