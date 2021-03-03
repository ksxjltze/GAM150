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

	private:
		bool MoveTo(AEVec2 pos);
		bool ReachedPos(AEVec2 pos);
		void SetWaypoints();

		bool foundPath;
		unsigned int nodeIndex;

		// Waypoints specific to this guard
		std::vector<AEVec2> waypoints;

		std::vector<A_Node*> path;

		AEVec2 distraction_position;
	};
}