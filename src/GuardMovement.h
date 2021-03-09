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

		inline const AEVec2& GetNextPos() const { return nextPos; }
		inline bool IsMoving() const { return isMoving; }
		bool IsChangingDir();

	private:
		bool MoveTo(AEVec2 pos);
		bool ReachedPos(AEVec2 pos);
		void SetWaypoints();

		bool isMoving;
		bool foundPath;
		unsigned int nodeIndex;

		AEVec2 nextPos;

		// Waypoints specific to this guard
		std::vector<AEVec2> waypoints;

		std::vector<A_Node*> path;

		AEVec2 distraction_position;
	};
}