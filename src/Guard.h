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
			STATE_DISTRACTED,
			STATE_TOTAL
		};

		Guard(GameObject* gameObject);

		void Start();
		void Update();

		inline void SetState(GUARD_STATE _state) { state = _state; }
		inline int GetID() const { return id; }

		void DistractGuard(AEVec2 const& pos);

	private:
		GUARD_STATE state;
		GuardMovement* movement;
		GuardVision* vision;
		static int id;
	};
}

