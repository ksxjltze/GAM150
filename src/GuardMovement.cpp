#include "GuardMovement.h"
#include <iostream>

StarBangBang::GuardMovement::GuardMovement(GameObject* gameObject) : Script(gameObject)
{
	SetWaypoints();
	std::cout << waypoints.size() << "\n";
}

void StarBangBang::GuardMovement::Patrol()
{
	//std::cout << "GUARD: PATROL" << "\n";
	double dt = AEFrameRateControllerGetFrameTime();
	gameObject->transform.position.x += 50.0 * dt;

	AEVec2 target = { 0, 0 }, dir = { 0, 0 };
	AEVec2 test = { 100, 10 };
	std::cout << waypoints.size() << "\n";
	
	AEVec2Sub(&target, &test, &gameObject->transform.position);
	AEVec2Scale(&dir, &test, dt);
	AEVec2Normalize(&dir, &dir);
	AEVec2Add(&gameObject->transform.position, &gameObject->transform.position, &dir);
}

void StarBangBang::GuardMovement::Chase()
{

}

void StarBangBang::GuardMovement::Distracted()
{

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