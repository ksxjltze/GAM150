#include "GuardVision.h"
#include "Guard.h"

using namespace StarBangBang;

GuardVision::GuardVision(GameObject* gameObject) : Script(gameObject)
{
	detected = false;
	player = nullptr;
	client = nullptr;
}

void GuardVision::Update()
{
	// update guard's vision stuff here
	// ...

	if (detected)
	{
		gameObject->GetComponent<Guard>()->SetState(Guard::GUARD_STATE::STATE_CHASE);
	}
}