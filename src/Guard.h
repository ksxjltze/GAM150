#pragma once
#include "ScriptComponent.h"
#include "GuardMovement.h"

namespace StarBangBang
{
	class Guard : public Script
	{
	private:
		enum class GUARD_STATE
		{
			STATE_PATROL = 0,
			STATE_CHASE,
			STATE_DISTRACTED,
			STATE_TOTAL
		};

	public:
		Guard(GameObject* gameObject);
		_Component* Clone(GameObject* obj, _Component*) { return new Guard(obj); }

		void Start();
		void Update();

	private:
		GUARD_STATE state;
	};
}

