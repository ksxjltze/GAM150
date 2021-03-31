#include "GuardMovement.h"
#include "Guard.h"
#include <iostream>

#include "BasicMeshShape.h"
#include "globals.h"

using namespace StarBangBang;

GuardMovement::GuardMovement(GameObject* gameObject)
	: Script(gameObject)
	, speed(GUARD::GUARD_SPEED)
	, distractedDuration(0.f)
	, nodeIndex(0)
	, waypointIndex(0)
	, pathSize(0)
	, lookForPath(false)
	, foundPath(false)
	, isMoving(false)
	, changedTargetPos(false)
	, idleForever(false)
	, turning(false)
	, usingWaypoints(false)
	, movingToLastWaypoint(true)
	, guard(nullptr)
	, rb(nullptr)
	, distractionNode(nullptr)
	, startPos{ 0, 0 }
	, targetPos{ 0, 0 }
	, endPos{ 0, 0 }
	, nextPos{ 0, 0 }
	, reachedEndOfPath{ false }
{
	//std::cout << waypoints.size() << "\n";

	//std::string text = "Guard ID: " + std::to_string(gameObject->GetComponent<Guard>()->GetID()) + "\n";
	//PRINT(text.c_str());
	//targetPos = waypoints.front();
}

void GuardMovement::Start()
{
	rb = gameObject->GetComponent<RigidBody>();
	rb->drag = 0.2f;

	guard = gameObject->GetComponent<Guard>();
}

void GuardMovement::Idle()
{
	//std::cout << "GUARD: IDLE" << "\n";

	// rotate between left, front, right, back sprites
	// ...

	isMoving = false;

	if (idleForever)
		return;

	// Return to patrol state
	if (guard->GetPrevState() == Guard::GUARD_STATE::STATE_DISTRACTED)
	{
		distractedDuration -= g_dt;
		if (distractedDuration <= 0.f)
		{
			guard->ChangeState(Guard::GUARD_STATE::STATE_PATROL);
			foundPath = false;
			distractedDuration = 0.f;
		}
	}
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


	if (!usingWaypoints)
	{
		if (!changedTargetPos)
		{
			targetPos = endPos;
		}
		else
		{
			targetPos = startPos;
		}
	}
	else
	{
		targetPos = waypoints[waypointIndex];
	}

	if (!foundPath)
	{
		LookForPath(targetPos);

		if (distractionNode)
			distractionNode->occupied = false;

		return;
	}

	MoveAlongPath();

	if (usingWaypoints && reachedEndOfPath)
	{
		if (movingToLastWaypoint)
		{
			++waypointIndex;

			if (waypointIndex >= waypoints.size())
			{
				movingToLastWaypoint = false; // now guard will go to waypoints in reverse order
				waypointIndex = static_cast<unsigned int>(waypoints.size() - 1);
			}
		}
		else
		{
			--waypointIndex;
			if (waypointIndex <= 0)
			{
				movingToLastWaypoint = true; // now guard will go to waypoints in order
				waypointIndex = 0;
			}
		}
	}
}

void GuardMovement::OnEnterDistracted()
{
	isMoving = false;
	speed = GUARD::GUARD_SPEED + 15.f;
	UnblockPreviousPath();
	LookForPath(targetPos);

	if (path.size() > 0)
		distractionNode = path.back();
}

void GuardMovement::Distracted()
{
	if (!foundPath)
		return;

	MoveAlongPath();

	if (reachedEndOfPath)
	{
		guard->ChangeState(Guard::GUARD_STATE::STATE_IDLE);
	}
}

void GuardMovement::OnExitDistracted()
{
	speed = GUARD::GUARD_SPEED;
}

void GuardMovement::OnEnterChase()
{
	isMoving = false;
	speed = GUARD::GUARD_SPEED + 20.f;
	UnblockPreviousPath();
	LookForPath(targetPos);
	nodeIndex = 1;
}

void GuardMovement::Chase()
{
	if (!foundPath)
		return;

	MoveAlongPath();

	if (reachedEndOfPath)
	{
		// send game over event
		MessageBus::Notify({ EventId::GAME_OVER, gameObject });
	}
}

void GuardMovement::MoveAlongPath()
{
	if (turning)
		return;
	
	if (gameObject->GetComponent<Guard>()->GetState() == Guard::GUARD_STATE::STATE_DISTRACTED)
	{
		pathSize = path.size() - 1;
	}
	else
	{
		pathSize = path.size();
	}

	if (nodeIndex < pathSize)
	{
		isMoving = true;
		nextPos = path[nodeIndex]->nodePos;

		float timer = 0.f;
		if (MoveTo(path[nodeIndex]->nodePos))
		{
			timer += g_dt;
			if (timer >= 0.01f)
			{
				path[nodeIndex]->occupied = false;
				++nodeIndex;
				timer = 0.f;
			}
		}
	}
	else
	{
		// deactivate interactable object
		// ...

		reachedEndOfPath = true;
		path.clear();
		nodeIndex = 0;
		foundPath = false;
		isMoving = false;
		changedTargetPos = !changedTargetPos;
	}
}

bool GuardMovement::MoveTo(AEVec2 pos)
{
	if (ReachedPos(pos))
	{
		//gameObject->transform.position = pos; // this snapping to position causes the obj to vanish
		return true;
	}

	AEVec2 dir = { 0, 0 };

	AEVec2Sub(&dir, &pos, &gameObject->transform.position);
	AEVec2Normalize(&dir, &dir);
	AEVec2Scale(&dir, &dir, speed);

	rb->AddVelocity(dir, 1.f);

	return false;
}

bool GuardMovement::ReachedPos(AEVec2 pos)
{
	float minDistToTarget = 10.f;
	return (AEVec2SquareDistance(&pos, &gameObject->transform.position) <= minDistToTarget * minDistToTarget);
}

void GuardMovement::SetWaypoints(const std::vector<AEVec2>& _waypoints)
{
	usingWaypoints = true;
	waypoints = _waypoints;
}

bool GuardMovement::IsChangingDir()
{
	AEVec2 currNode, prevNode;
	
	prevNode = path[nodeIndex]->nodePos;
	size_t index = static_cast<size_t>(nodeIndex) + static_cast<size_t>(1);

	if (index < path.size())
		currNode = path[index]->nodePos;
	else
		currNode = prevNode;

	AEVec2Normalize(&currNode, &currNode);
	AEVec2Normalize(&prevNode, &prevNode);
	float dpResult = AEVec2DotProduct(&currNode, &prevNode);

	return (dpResult < 0.f);

	/*if ((int)currNode.x == (int)prevNode.x)
		if ((int)currNode.y != (int)prevNode.y)
			return true;

	if ((int)currNode.y == (int)prevNode.y)
		if ((int)currNode.x != (int)prevNode.x)
			return true;

	return false;*/
	//return (currNode.x != prevNode.x || currNode.y != prevNode.y);
}

void GuardMovement::LookForPath(const AEVec2& pos)
{
	turning = false;
	lookForPath = true;

	if (lookForPath)
	{
		if (foundPath) // changing path midway into moving along the path
		{
			nodeIndex = 0;
		}

		path = PathFinder::SearchForPath(gameObject->transform.position, pos);
		foundPath = (path.size() > 0);
		lookForPath = false;
		reachedEndOfPath = false;
	}
}

void GuardMovement::SetStartEndPos(const AEVec2& start, const AEVec2& end, bool _idleForever)
{
	gameObject->SetPos(start);
	startPos = start;
	endPos = end;
	idleForever = _idleForever;
}

void GuardMovement::UnblockPreviousPath()
{
	for (A_Node* n : path)
	{
		n->occupied = false;
	}

	path.clear();
}