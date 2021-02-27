#include "GuardMovement.h"
#include "GuardVision.h"
#include "Guard.h"
#include <iostream>

using namespace StarBangBang;

StarBangBang::GuardMovement::GuardMovement(GameObject* gameObject) : Script(gameObject)
{
	SetWaypoints();
	std::cout << waypoints.size() << "\n";
}

void StarBangBang::GuardMovement::Idle()
{

}

void StarBangBang::GuardMovement::Patrol()
{
	//std::cout << "GUARD: PATROL" << "\n";
	float dt = static_cast<float>(AEFrameRateControllerGetFrameTime());
	gameObject->transform.position.x += 50.0 * dt;

	AEVec2 target = { 0, 0 }, dir = { 0, 0 };
	AEVec2 test = { 100, 10 };
	//std::cout << waypoints.size() << "\n";
	
	AEVec2Sub(&target, &test, &gameObject->transform.position);
	AEVec2Scale(&dir, &waypoints.front(), dt);
	AEVec2Normalize(&dir, &dir);
	AEVec2Add(&gameObject->transform.position, &gameObject->transform.position, &dir);
}

void StarBangBang::GuardMovement::Chase()
{
	// chase player
	// ...

	// if can't see player after some time, change to patrol state
	static double time = 0.0;
	time += AEFrameRateControllerGetFrameTime();
	if (time >= CHASE_TIME)
	{
		if (!gameObject->GetComponent<GuardVision>()->GetDetectedPlayer())
		{
			gameObject->GetComponent<Guard>()->SetState(Guard::GUARD_STATE::STATE_PATROL);
			time = 0.0;
		}
	}
}

void StarBangBang::GuardMovement::Distracted()
{
	// go to interactable object
	// ...
}

void StarBangBang::GuardMovement::SetWaypoints()
{
	std::cout << "GUARD: SETTING WAYPOINTS\n";
	// Test
	waypoints.push_back({ 100, 10 });


	// ***********************************

	// Read from file
	// ...

	// Set waypoints specfic to this guard
	// ...
}