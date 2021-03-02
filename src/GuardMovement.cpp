#include "GuardMovement.h"
#include "GuardVision.h"
#include "Guard.h"
#include <iostream>
#include <string>

using namespace StarBangBang;

GuardMovement::GuardMovement(GameObject* gameObject)
	: Script(gameObject)
{
	SetWaypoints();
	//std::cout << waypoints.size() << "\n";

	std::string text = "Guard ID: " + std::to_string(gameObject->GetComponent<Guard>()->GetID()) + "\n";
	PRINT(text.c_str());
}

void GuardMovement::Idle()
{
	//std::cout << "GUARD: IDLE" << "\n";

	// rotate between left, front, right, back sprites
	// ...
}

void GuardMovement::Patrol()
{
	//std::cout << "GUARD: PATROL" << "\n";

	/*AEVec2 target = { 0, 0 }, dir = { 0, 0 };
	AEVec2 test = { 100, 10 };

	AEVec2Sub(&target, &test, &gameObject->transform.position);
	AEVec2Scale(&dir, &waypoints.front(), dt);
	AEVec2Normalize(&dir, &dir);
	AEVec2Add(&gameObject->transform.position, &gameObject->transform.position, &dir);*/

	MoveTo(waypoints.front());
}

void GuardMovement::Distracted()
{
	//std::cout << "GUARD: DISTRACTED" << "\n";

	// go to interactable object
	if (MoveTo(distraction_position))
	{
		// deactivate interactable object
	}
}

bool GuardMovement::MoveTo(AEVec2 pos)
{
	float minDistToTarget = 2.f;
	if (AEVec2SquareDistance(&pos, &gameObject->transform.position) <= minDistToTarget * minDistToTarget)
		return true;

	double dt = AEFrameRateControllerGetFrameTime();
	AEVec2 dir = { 0, 0 };

	AEVec2Sub(&dir, &pos, &gameObject->transform.position);
	AEVec2Normalize(&dir, &dir);
	AEVec2Scale(&dir, &dir, dt * 300.0);
	AEVec2Add(&gameObject->transform.position, &gameObject->transform.position, &dir);

	return false;
}

void GuardMovement::SetWaypoints()
{
	//std::cout << "GUARD: SETTING WAYPOINTS\n";
	// Test
	waypoints.push_back({ 100, 10 });


	// ***********************************

	// Read from file
	// ...

	// Set waypoints specfic to this guard
	// ...
}