#include "GuardMovement.h"
#include "GuardVision.h"
#include "Guard.h"
#include <iostream>
#include <string>

using namespace StarBangBang;

GuardMovement::GuardMovement(GameObject* gameObject) : Script(gameObject)
{
	SetWaypoints();
	//std::cout << waypoints.size() << "\n";

	std::string text = "Guard ID: " + std::to_string(gameObject->GetComponent<Guard>()->GetID()) + "\n";
	PRINT(text.c_str());
}

void GuardMovement::Idle()
{

}

void GuardMovement::Patrol()
{
	//std::cout << "GUARD: PATROL" << "\n";
	double dt = AEFrameRateControllerGetFrameTime();
	gameObject->transform.position.x += 50.0 * dt;

	AEVec2 target = { 0, 0 }, dir = { 0, 0 };
	AEVec2 test = { 100, 10 };
	//std::cout << waypoints.size() << "\n";
	
	AEVec2Sub(&target, &test, &gameObject->transform.position);
	AEVec2Scale(&dir, &waypoints.front(), dt);
	AEVec2Normalize(&dir, &dir);
	AEVec2Add(&gameObject->transform.position, &gameObject->transform.position, &dir);
}

void GuardMovement::Distracted()
{
	// go to interactable object
	// ...
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