#include "Guard.h"

using namespace StarBangBang;

int Guard::id = -1;

Guard::Guard(GameObject* gameObject)
	: Script(gameObject)
	, state(GUARD_STATE::STATE_IDLE)
	, movement(nullptr)
{
	++id;
}

void Guard::Start()
{
	movement = gameObject->GetComponent<GuardMovement>();
	vision = gameObject->GetComponent<GuardVision>();
}

void Guard::Update()
{
	switch (state)
	{
	case Guard::GUARD_STATE::STATE_IDLE:
		movement->Idle();
		vision->GetDetector()->SpanVision(-90.f, 90.f, 50.f);
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