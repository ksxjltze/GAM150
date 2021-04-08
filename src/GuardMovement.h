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
		GuardMovement(GameObject* gameObject);

		void Start();
		void Update() {}

		void Idle();
		void Patrol();

		void OnEnterDistracted();
		void Distracted();
		void OnExitDistracted();

		void OnEnterChase();
		void Chase();

		void LookForPath(const AEVec2& pos);
		void SetStartEndPos(const AEVec2& start, const AEVec2& end, bool _idleForever = false);
		void UnblockPreviousPath();

		inline const AEVec2& GetNextPos() const { return nextPos; }
		inline bool IsMoving() const { return isMoving; }
		inline void SetSpeed(float _speed) { speed = _speed; }
		bool IsChangingDir();

		inline void SetTurning(bool _turning) { turning = _turning; }
		inline bool IsTurning() const { return turning; }

		inline void SetTargetPos(const AEVec2 pos) { targetPos = pos; }
		inline const AEVec2& GetTargetPos() const { return targetPos; }

		inline void SetDistractionDuration(float duration) { distractedDuration = duration; }

		inline bool GetGoingToPatrolPoint() const { return goingToPatrolPoint; }

		void SetWaypoints(const std::vector<AEVec2>& _waypoints);

	private:
		void MoveAlongPath();
		bool MoveTo(AEVec2 pos);
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

		// If want to go to certain positions instead of
		// just using a start and end pos
		std::vector<AEVec2> waypoints;

		std::vector<A_Node*> path;

		Guard* guard;

		RigidBody* rb;
		A_Node* distractionNode;
	};
}