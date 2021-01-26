#include "Guard.h"

StarBangBang::Guard::Guard(GameObject* gameObject) : Script(gameObject)
{
	// Guard's starting state
	state = GUARD_STATE::STATE_PATROL;
}

void StarBangBang::Guard::Start()
{

}

void StarBangBang::Guard::Update()
{
	gameObject->GetComponent<GuardMovement>()->Patrol();
}