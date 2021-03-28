#include "Guard.h"
#include "DistractionEvent.h"

using namespace StarBangBang;

int Guard::id = -1;

Guard::Guard(GameObject* gameObject)
	: Script(gameObject), Listener()
	, state(GUARD_STATE::STATE_PATROL)
	, movement(nullptr)
	, vision(nullptr)
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
	
	SetState(GUARD_STATE::STATE_DISTRACTED);

	if (AEVec2Distance(&distractionPos, &gameObject->transform.position) <= alertRadius)
	{
		std::cout << "GUARD DISTRACTED " << ++distractCount << std::endl;

	}
}
