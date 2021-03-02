#include "Guard.h"

using namespace StarBangBang;

int Guard::id = -1;

Guard::Guard(GameObject* gameObject) 
	: Script(gameObject),
	  state(GUARD_STATE::STATE_PATROL),
	  movement(nullptr)
{
	++id;
}

void Guard::Start()
{
	movement = gameObject->GetComponent<GuardMovement>();
}

void Guard::Update()
{
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