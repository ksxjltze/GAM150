#pragma once
#include "ScriptComponent.h"

namespace StarBangBang
{
	class GuardVision : public Script
	{
	public:
		GuardVision(GameObject* gameObject);

		void Update();

		inline void SetDetectedPlayer(bool _detected) { detected_player = _detected; }
		inline bool GetDetectedPlayer() { return detected_player; }

	private:
		bool detected_player;
	};
}