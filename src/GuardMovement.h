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
		void Distracted();

		void LookForPath(const AEVec2& pos);
		void SetStartEndPos(const AEVec2& start, const AEVec2& end, bool _idleForever = false);
		void UnblockPatrolPath();

		inline const AEVec2& GetNextPos() const { return nextPos; }
		inline bool IsMoving() const { return isMoving; }
		inline void SetSpeed(float _speed) { speed = _speed; }
		bool IsChangingDir();

		inline void SetTurning(bool _turning) { turning = _turning; }
		inline bool IsTurning() const { return turning; }

	private:
		void MoveAlongPath();
		bool MoveTo(AEVec2 pos);
		bool ReachedPos(AEVec2 pos);
		void SetWaypoints();

		bool isMoving;
		bool lookForPath;
		bool foundPath;
		bool reachedEndOfPath;
		bool changedTargetPos;
		bool idleForever;

		bool turning;

		float speed;
		float idleTimer;

		unsigned int nodeIndex;
		unsigned int pathSize;

		AEVec2 targetPos;
		AEVec2 startPos;
		AEVec2 endPos;

		AEVec2 nextPos;

		// Waypoints specific to this guard
		std::vector<AEVec2> waypoints; // to use in case pathfinding causes fps drops

		std::vector<A_Node*> path;

		Guard* guard;

		RigidBody* rb;
	};
}