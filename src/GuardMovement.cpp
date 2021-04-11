/*!*********************************************************************
\title	  Captain Stealth
\file     GuardMovement.cpp
\author   Liew Ruiheng Rayner (100%)
\par      DP email: r.liew\@digipen.edu
\date     10/04/2021

\brief
		  This file contains the function definitions of the 
		  GuardMovement script class

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
***********************************************************************/

#include "GuardMovement.h"
#include "Guard.h"
#include "BasicMeshShape.h"
#include "globals.h"

using namespace StarBangBang;

/*!*********************************************************************
\brief
	Non-default constructor

\param gameObject
	The game object that will use this script
***********************************************************************/
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
	, goingToPatrolPoint(false)
	, guard(nullptr)
	, rb(nullptr)
	, distractionNode(nullptr)
	, startPos{ 0, 0 }
	, targetPos{ 0, 0 }
	, endPos{ 0, 0 }
	, nextPos{ 0, 0 }
	, reachedEndOfPath{ false }
{
}

/*!*********************************************************************
\brief
	Sets up the script
***********************************************************************/
void GuardMovement::Start()
{
	rb = gameObject->GetComponent<RigidBody>();
	rb->drag = 0.2f;

	guard = gameObject->GetComponent<Guard>();
}

/*!*********************************************************************
\brief
	Guard's idle behaviour
***********************************************************************/
void GuardMovement::Idle()
{
	isMoving = false;

	if (idleForever)
		return;

	// Return to patrol state if previous state before idle was distracted
	if (guard->GetPrevState() == Guard::GUARD_STATE::STATE_DISTRACTED)
	{
		distractedDuration -= g_dt;
		if (distractedDuration <= 0.f)
		{
			goingToPatrolPoint = true;
			guard->ChangeState(Guard::GUARD_STATE::STATE_PATROL);
			foundPath = false;
			distractedDuration = 0.f;
		}
	}
}

/*!*********************************************************************
\brief
	Guard's patrol behaviour
***********************************************************************/
void GuardMovement::Patrol()
{
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
				movingToLastWaypoint = true; // now guard will go to waypoints in list order
				waypointIndex = 0;
			}
		}
	}
	else if (reachedEndOfPath)
	{
		goingToPatrolPoint = false;
	}
}

/*!*********************************************************************
\brief
	Set variables upon entering distracted state
***********************************************************************/
void GuardMovement::OnEnterDistracted()
{
	isMoving = false;
	speed = GUARD::GUARD_SPEED + 35.f;
	UnblockPreviousPath();
	LookForPath(targetPos);

	if (path.size() > 0)
		distractionNode = path.back();
}

/*!*********************************************************************
\brief
	Guard's distracted behaviour
***********************************************************************/
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

/*!*********************************************************************
\brief
	Set variables upon leaving distracted state
***********************************************************************/
void GuardMovement::OnExitDistracted()
{
	speed = GUARD::GUARD_SPEED;
}

/*!*********************************************************************
\brief
	Set variables upon entering chase state
***********************************************************************/
void GuardMovement::OnEnterChase()
{
	isMoving = false;
	speed = GUARD::GUARD_SPEED + 35.f;
	UnblockPreviousPath();
	LookForPath(targetPos);
	nodeIndex = 1;
}

/*!*********************************************************************
\brief
	Guard's chase behaviour
***********************************************************************/
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

/*!*********************************************************************
\brief
	Move along a searched path to the target position
***********************************************************************/
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

/*!*********************************************************************
\brief
	Moves guard to a given position then checks if guard has reached
	that position

\param pos
	The target position to move to

\return
	Whether the guard has reached the target position
***********************************************************************/
bool GuardMovement::MoveTo(AEVec2 pos)
{
	if (ReachedPos(pos))
		return true;

	AEVec2 dir = { 0, 0 };

	AEVec2Sub(&dir, &pos, &gameObject->transform.position);
	AEVec2Normalize(&dir, &dir);
	AEVec2Scale(&dir, &dir, speed);

	rb->AddVelocity(dir, 1.f);

	return false;
}

/*!*********************************************************************
\brief
	Get if the guard has reached a given position

\param pos
	The target position that the guard is supposed to reach

\return
	Whether the guard has reached the given position
***********************************************************************/
bool GuardMovement::ReachedPos(AEVec2 pos)
{
	float minDistToTarget = 10.f;
	return (AEVec2SquareDistance(&pos, &gameObject->transform.position) <= minDistToTarget * minDistToTarget);
}

/*!*********************************************************************
\brief
	Set the waypoints for the guard

\param _waypoints
	The list of points for the guard to patrol
***********************************************************************/
void GuardMovement::SetWaypoints(const std::vector<AEVec2>& _waypoints)
{
	usingWaypoints = true;
	waypoints = _waypoints;
}

/*!*********************************************************************
\brief
	Search for a path to a given position

\param pos
	The position to look for a path to
***********************************************************************/
void GuardMovement::LookForPath(const AEVec2& pos)
{
	turning = false;
	lookForPath = true;

	if (lookForPath)
	{
		if (foundPath) // if changing path midway while moving along the path
		{
			nodeIndex = 0;
		}

		PathFinder::SearchForPath(gameObject->transform.position, pos, path);
		foundPath = (path.size() > 0);
		lookForPath = false;
		reachedEndOfPath = false;
	}
}

/*!*********************************************************************
\brief
	Set the guard's starting and ending waypoints

\param start
	The starting waypoint

\param end
	The ending waypoint

\param _idleForever
	Whether the guard will be in idle state throughout the game
***********************************************************************/
void GuardMovement::SetStartEndPos(const AEVec2& start, const AEVec2& end, bool _idleForever)
{
	gameObject->SetPos(start);
	startPos = start;
	endPos = end;
	idleForever = _idleForever;
}

/*!*********************************************************************
\brief
	Unblock previous path that the guard took/was intending to take
***********************************************************************/
void GuardMovement::UnblockPreviousPath()
{
	for (A_Node* n : path)
	{
		n->occupied = false;
	}

	path.clear();
}