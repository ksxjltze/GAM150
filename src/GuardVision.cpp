
#include "GuardVision.h"
#include "Guard.h"

using namespace StarBangBang;

GuardVision::GuardVision(GameObject* gameObject) 
	: Script(gameObject)
	, detected_player(false)
{
	player = nullptr;
	client = nullptr;
}

void GuardVision::Update()
{
	// update guard's vision stuff here
	// ...

	if (detected_player)
	{
		// notify event manager: game over
	}
}