#include "GuardVision.h"
#include "Guard.h"

using namespace StarBangBang;

StarBangBang::GuardVision::GuardVision(GameObject* gameObject) : Script(gameObject)
{
	detected_player = false;
}

void StarBangBang::GuardVision::Update()
{
	// update guard's vision stuff here
	// ...

	if (detected_player)
	{
		gameObject->GetComponent<Guard>()->SetState(Guard::GUARD_STATE::STATE_CHASE);
	}
}