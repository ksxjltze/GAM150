#pragma once
#include "ScriptComponent.h"
#include "GuardMovement.h"
#include "GuardVision.h"

namespace StarBangBang
{
	class Guard : public Script
	{
	public:
		enum class GUARD_STATE
		{
			STATE_IDLE = 0,
			STATE_PATROL,
			STATE_CHASE,
			STATE_DISTRACTED,
			STATE_TOTAL
		};

		Guard(GameObject* gameObject);

		void Start();
		void Update();

		inline void SetState(GUARD_STATE _state) { state = _state; }
		//void NotifyGuard(GameObject* gameObject);
		inline int GetID() const { return id; }

	private:
		GUARD_STATE state;
		GuardVision* vision;
		GuardMovement* movement;
		static int id;
	};
}

