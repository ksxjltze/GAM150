#pragma once
#include "ScriptComponent.h"
#include "PathFinder.h"
#include <vector>

namespace StarBangBang
{
	class GuardMovement : public Script
	{
	private:
		const float SPEED = 150.f;
	public:
		GuardMovement(GameObject* gameObject);

		void Start() {}
		void Update() {}

		void Idle();
		void Patrol();
		void Distracted();

		void LookForPath(const AEVec2& pos);

		inline const AEVec2& GetNextPos() const { return nextPos; }
		inline bool IsMoving() const { return isMoving; }
		bool IsChangingDir();

	private:
		void MoveAlongPath();
		bool MoveTo(AEVec2 pos);
		bool ReachedPos(AEVec2 pos);
		void SetWaypoints();

		bool isMoving;
		bool lookForPath;
		bool foundPath;
		unsigned int nodeIndex;

		AEVec2 nextPos;

		// Waypoints specific to this guard
		std::vector<AEVec2> waypoints;

		std::vector<A_Node*> path;

		//AEVec2 targetPos; // the end position of the path
	};
}