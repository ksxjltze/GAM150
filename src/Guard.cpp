#include "Guard.h"

StarBangBang::Guard::Guard(GameObject* gameObject) : Script(gameObject)
{
	// Guard's starting state
	state = GUARD_STATE::STATE_PATROL;
	vision = nullptr;
	movement = nullptr;
}

void StarBangBang::Guard::Start()
{
	vision = gameObject->GetComponent<GuardVision>();
	movement = gameObject->GetComponent<GuardMovement>();
}

void StarBangBang::Guard::Update()
{
	vision->Update();

	switch (state)
	{
	case StarBangBang::Guard::GUARD_STATE::STATE_IDLE:
		movement->Idle();
		break;
	case StarBangBang::Guard::GUARD_STATE::STATE_PATROL:
		movement->Patrol();
		break;
	case StarBangBang::Guard::GUARD_STATE::STATE_CHASE:
		movement->Chase();
		break;
	case StarBangBang::Guard::GUARD_STATE::STATE_DISTRACTED:
		movement->Distracted();
		break;
	default:
		break;
	}
}