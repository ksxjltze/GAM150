#include "Guard.h"
#include "DistractionEvent.h"

using namespace StarBangBang;

Guard::Guard(GameObject* gameObject)
	: Script(gameObject), Listener()
	, state(GUARD_STATE::STATE_PATROL)
	, prevState(GUARD_STATE::STATE_NONE)
	, movement(nullptr)
	, vision(nullptr)
	, id(0)
{
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
		Listener::open = false;
		break;
	default:
		break;
	}
}

void StarBangBang::Guard::onNotify(Event e)
{
	if (e.id == EventId::DISTRACTION)
	{
		DistractionEvent distraction = std::any_cast<DistractionEvent>(e.context);
		DistractGuard(distraction.gameObject->GetPos());
	}
}

void StarBangBang::Guard::DistractGuard(AEVec2 const& pos)
{
	static int distractCount = 0;
	AEVec2 distractionPos = pos;
	float alertRadius = 400.0f;

	if (AEVec2Distance(&distractionPos, &gameObject->transform.position) <= alertRadius)
	{
		//std::cout << "GUARD DISTRACTED! GUARD ID: " << id << std::endl;
		SetState(GUARD_STATE::STATE_DISTRACTED);
		movement->UnblockPatrolPath();
		movement->LookForPath(distractionPos);
	}
}

void Guard::SetState(GUARD_STATE _state)
{
	prevState = state;
	state = _state;
}