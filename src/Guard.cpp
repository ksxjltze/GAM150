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
	, roomNum(0)
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
	if (state != Guard::GUARD_STATE::STATE_CHASE)
	{
		AEVec2 targetPos;
		if (vision->GetDetector()->GetDetected(targetPos))
		{
			MessageBus::Notify({ EventId::PRINT_TEXT, std::string("DETECTED!") });
			movement->SetTargetPos(targetPos);
			ChangeState(Guard::GUARD_STATE::STATE_CHASE);
		}
	}

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
	case Guard::GUARD_STATE::STATE_CHASE:
		movement->Chase();
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
	case Guard::GUARD_STATE::STATE_CHASE:
		movement->OnEnterChase();
		break;
	default:
		break;
	}

	state = _state;
}