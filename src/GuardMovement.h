#pragma once
#include "ScriptComponent.h"
#include <vector>

namespace StarBangBang
{
	class GuardMovement : public Script
	{
	public:
		GuardMovement(GameObject* gameObject);

		void Idle();
		void Patrol();
		void Chase();
		void Distracted();

	private:
		void SetWaypoints();

		const double CHASE_TIME = 5.0;

		// Waypoints specific to this guard
		std::vector<AEVec2> waypoints;
	};
}