#include "GuardMovement.h"
#include "GuardVision.h"
#include "Guard.h"
#include "Utils.h"
#include <iostream>

#include "BasicMeshShape.h"

using namespace StarBangBang;

GuardMovement::GuardMovement(GameObject* gameObject)
	: Script(gameObject)
	, nodeIndex(0)
	, foundPath(false)
{
	SetWaypoints();
	//std::cout << waypoints.size() << "\n";

	std::string text = "Guard ID: " + std::to_string(gameObject->GetComponent<Guard>()->GetID()) + "\n";
	PRINT(text.c_str());
	distraction_position = waypoints.front();
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

	//MoveTo(waypoints.front());
	Distracted();
}

void GuardMovement::Distracted()
{
	if (AEInputCheckTriggered(VK_LBUTTON))
	{
		if (foundPath) // changing path midway into moving along the path
		{
			nodeIndex = 0;
		}

		distraction_position = GetMouseWorldPos();
		path = PathFinder::SearchForPath(gameObject->transform.position, distraction_position);
		foundPath = (path.size() > 0);
	}

	if (foundPath)
	{
		for (const A_Node* n : path)
		{
			DrawCircle(10.0f, n->nodePos);
		}

		if (nodeIndex < path.size())
		{
			nextPos = path[nodeIndex]->nodePos;
			//PRINT("target: %f, %f\n", nextPos.x, nextPos.y);
				
			float timer = 0.f;
			if (MoveTo(path[nodeIndex]->nodePos))
			{
				timer += AEFrameRateControllerGetFrameTime();
				if (timer >= 0.01f)
				{
					++nodeIndex;
					timer = 0.f;
				}
			}
		}
		else
		{
			// deactivate interactable object
			// ...

			path.clear();
			nodeIndex = 0;
			foundPath = false;
		}
	}
}

bool GuardMovement::MoveTo(AEVec2 pos)
{
	if (ReachedPos(pos))
	{
		//gameObject->transform.position = pos; // this snapping to position causes the obj to vanish
		return true;
	}

	double dt = AEFrameRateControllerGetFrameTime();
	AEVec2 dir = { 0, 0 };

	AEVec2Sub(&dir, &pos, &gameObject->transform.position);
	AEVec2Normalize(&dir, &dir);
	AEVec2Scale(&dir, &dir, dt * SPEED);
	AEVec2Add(&gameObject->transform.position, &gameObject->transform.position, &dir);

	return false;
}

bool GuardMovement::ReachedPos(AEVec2 pos)
{
	float minDistToTarget = 2.f;
	return (AEVec2SquareDistance(&pos, &gameObject->transform.position) <= minDistToTarget * minDistToTarget);
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