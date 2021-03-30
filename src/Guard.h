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
			STATE_NONE = 0,
			STATE_IDLE,
			STATE_PATROL,
			STATE_DISTRACTED,
			STATE_TOTAL
		};

		Guard(GameObject* gameObject);

		void Start();
		void Update();

		void SetState(GUARD_STATE _state);
		inline GUARD_STATE GetState() const { return state; }
		inline GUARD_STATE GetPrevState() const { return prevState; }
		inline void SetID(size_t _id) { id = _id; }
		inline size_t GetID() const { return id; }

	private:
		GUARD_STATE state;
		GUARD_STATE prevState;

		GuardMovement* movement;
		GuardVision* vision;
		size_t id;
	};
}

