#include "Guard.h"

using namespace StarBangBang;

int Guard::id = -1;

Guard::Guard(GameObject* gameObject) : Script(gameObject)
{
	// Guard's starting state
	state = GUARD_STATE::STATE_PATROL;
	vision = nullptr;
	movement = nullptr;
	++id;
}

void Guard::Start()
{
	vision = gameObject->GetComponent<GuardVision>();
	movement = gameObject->GetComponent<GuardMovement>();
}

void Guard::Update()
{
	vision->Update();

	switch (state)
	{
	case Guard::GUARD_STATE::STATE_IDLE:
		movement->Idle();
		break;
	case Guard::GUARD_STATE::STATE_PATROL:
		movement->Patrol();
		break;
	case Guard::GUARD_STATE::STATE_DISTRACTED:
		movement->Distracted();
		break;
	default:
		break;
	}
}