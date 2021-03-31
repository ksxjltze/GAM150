#include "Guard.h"
#include "Text.h"

using namespace StarBangBang;

Guard::Guard(GameObject* gameObject)
	: Script(gameObject)
	, state(GUARD_STATE::STATE_PATROL)
	, prevState(GUARD_STATE::STATE_NONE)
	, movement(nullptr)
	, vision(nullptr)
	, id(0)
{
}

void Guard::Start()
{
	// display guard id for debugging
	gameObject->GetComponent<Text>()->SetText(std::to_string(id));

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

void Guard::ChangeState(GUARD_STATE _state)
{
	prevState = state;

	switch (_state)
	{
	case Guard::GUARD_STATE::STATE_IDLE:
		break;
	case Guard::GUARD_STATE::STATE_PATROL:
		break;
	case Guard::GUARD_STATE::STATE_DISTRACTED:
		movement->OnEnterDistracted();
		break;
	default:
		break;
	}

	state = _state;
}