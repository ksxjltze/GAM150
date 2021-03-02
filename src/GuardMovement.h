#pragma once
#include "ScriptComponent.h"
#include <vector>

namespace StarBangBang
{
	class GuardMovement : public Script
	{
	public:
		GuardMovement(GameObject* gameObject);

		void Start() {}
		void Update() {}

		void Idle();
		void Patrol();
		void Distracted();

	private:
		bool MoveTo(AEVec2 pos);
		void SetWaypoints();

		// Waypoints specific to this guard
		std::vector<AEVec2> waypoints;

		AEVec2 distraction_position;
	};
}