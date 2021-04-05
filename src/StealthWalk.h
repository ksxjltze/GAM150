#pragma once
#include "ScriptComponent.h"
#include "ImageComponent.h"

namespace StarBangBang
{
	class StealthWalk : public Script
	{
	public:
		StealthWalk(GameObject* gameObject);
		void Start();
		void Update();
		bool IsInvisible() { return invisible; }
		float GetTimer() { return timer; }
		float GetCooldown() { return cooldown; }
	private:
		ImageComponent* image;

		float timer;
		float cooldown;
		bool invisible = false;
	};
}