#pragma once
#include "ScriptComponent.h"
#include <vector>

namespace StarBangBang
{
	class GuardMovement : public Script
	{
	public:
		GuardMovement(GameObject* gameObject);
		Component* Clone(GameObject* obj, Component*) { return new GuardMovement(obj); }

		void Patrol();
		void Chase();
		void Distracted();

	private:
		void SetWaypoints();

		// Waypoints specific to this guard
		std::vector<AEVec2> waypoints;
	};
}