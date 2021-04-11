/*!*********************************************************************
\title	  Captain Stealth
\file     GuardMovement.h
\author   Liew Ruiheng Rayner (100%)
\par      DP email: r.liew\@digipen.edu
\date     10/04/2021

\brief
		  This file contains the GuardMovement script class

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
***********************************************************************/

#pragma once
#include "ScriptComponent.h"
#include "PathFinder.h"
#include "Physics.h"
#include <vector>
#include "Listener.h"

namespace StarBangBang
{
	class Guard;

	class GuardMovement : public Script
	{
	public:
		/*!*********************************************************************
		\brief
			Non-default constructor

		\param gameObject
			The game object that will use this script
		***********************************************************************/
		GuardMovement(GameObject* gameObject);

		/*!*********************************************************************
		\brief
			Sets up the script
		***********************************************************************/
		void Start();

		/*!*********************************************************************
		\brief
			Updates the script
		***********************************************************************/
		void Update() {}

		/*!*********************************************************************
		\brief
			Guard's idle behaviour
		***********************************************************************/
		void Idle();

		/*!*********************************************************************
		\brief
			Guard's patrol behaviour
		***********************************************************************/
		void Patrol();

		/*!*********************************************************************
		\brief
			Set variables upon entering distracted state
		***********************************************************************/
		void OnEnterDistracted();

		/*!*********************************************************************
		\brief
			Guard's distracted behaviour
		***********************************************************************/
		void Distracted();

		/*!*********************************************************************
		\brief
			Set variables upon leaving distracted state
		***********************************************************************/
		void OnExitDistracted();

		/*!*********************************************************************
		\brief
			Set variables upon entering chase state
		***********************************************************************/
		void OnEnterChase();

		/*!*********************************************************************
		\brief
			Guard's chase behaviour
		***********************************************************************/
		void Chase();

		/*!*********************************************************************
		\brief
			Search for a path to a given position

		\param pos
			The position to look for a path to
		***********************************************************************/
		void LookForPath(const AEVec2& pos);

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
		void SetStartEndPos(const AEVec2& start, const AEVec2& end, bool _idleForever = false);

		/*!*********************************************************************
		\brief
			Unblock previous path that the guard took/was intending to take
		***********************************************************************/
		void UnblockPreviousPath();

		/*!*********************************************************************
		\brief
			Get the next position of the path

		\return
			The next position of the path
		***********************************************************************/
		inline const AEVec2& GetNextPos() const { return nextPos; }

		/*!*********************************************************************
		\brief
			Check if guard is currently moving

		\return
			Whether the guard is moving
		***********************************************************************/
		inline bool IsMoving() const { return isMoving; }

		/*!*********************************************************************
		\brief
			Set movement speed of the guard

		\param _speed
			The movement speed of the guard
		***********************************************************************/
		inline void SetSpeed(float _speed) { speed = _speed; }

		/*!*********************************************************************
		\brief
			Set if the guard is changing direction

		\param _turning
			Whether the guard is changing direction
		***********************************************************************/
		inline void SetTurning(bool _turning) { turning = _turning; }

		/*!*********************************************************************
		\brief
			Get if the guard is changing direction

		\return
			Whether the guard is turning
		***********************************************************************/
		inline bool IsTurning() const { return turning; }

		/*!*********************************************************************
		\brief
			Set the target position that the path will end at

		\param pos
			The target position
		***********************************************************************/
		inline void SetTargetPos(const AEVec2 pos) { targetPos = pos; }

		/*!*********************************************************************
		\brief
			Get the target position that the path will end at

		\return
			The target position
		***********************************************************************/
		inline const AEVec2& GetTargetPos() const { return targetPos; }

		/*!*********************************************************************
		\brief
			Set the guard's distracted duration

		\param duration
			The amount of time to get distracted by
		***********************************************************************/
		inline void SetDistractionDuration(float duration) { distractedDuration = duration; }

		/*!*********************************************************************
		\brief
			Get if the guard is returning to patrol point (used when the guard is
			coming from a distracted state)

		\return
			Whether the guard is returning to patrol point
		***********************************************************************/
		inline bool GetGoingToPatrolPoint() const { return goingToPatrolPoint; }

		/*!*********************************************************************
		\brief
			Set the waypoints for the guard

		\param _waypoints
			The list of points for the guard to patrol
		***********************************************************************/
		void SetWaypoints(const std::vector<AEVec2>& _waypoints);

	private:
		/*!*********************************************************************
		\brief
			Move along a searched path to the target position
		***********************************************************************/
		void MoveAlongPath();

		/*!*********************************************************************
		\brief
			Moves guard to a given position then checks if guard has reached
			that position

		\param pos
			The target position to move to
		
		\return
			Whether the guard has reached the target position
		***********************************************************************/
		bool MoveTo(AEVec2 pos);

		/*!*********************************************************************
		\brief
			Get if the guard has reached a given position

		\param pos
			The target position that the guard is supposed to reach

		\return
			Whether the guard has reached the given position
		***********************************************************************/
		bool ReachedPos(AEVec2 pos);

		bool isMoving;
		bool lookForPath;
		bool foundPath;
		bool reachedEndOfPath;
		bool changedTargetPos;
		bool idleForever;

		bool turning;
		bool usingWaypoints;
		bool movingToLastWaypoint;
		bool goingToPatrolPoint;

		float speed;
		float distractedDuration;

		unsigned int nodeIndex;
		unsigned int waypointIndex;
		size_t pathSize;

		AEVec2 targetPos;
		AEVec2 startPos;
		AEVec2 endPos;

		AEVec2 nextPos;

		// If want to go to certain positions instead of just using a start and end pos
		std::vector<AEVec2> waypoints;

		std::vector<A_Node*> path;

		Guard* guard;

		RigidBody* rb;
		A_Node* distractionNode;
	};
}