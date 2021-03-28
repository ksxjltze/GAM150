#pragma once
#include "ScriptComponent.h"
#include "GraphicsManager.h"

namespace StarBangBang
{
	class RigidBody;
	class GuardMovement;
	enum class guard_direction;

	class GuardAnim : public Script
	{
	public:
		GuardAnim(GameObject* gameObject);
		void Start();
		void Update();
		static void Load(GraphicsManager& gfxMgr);

	private:
		RigidBody* rb;
		GuardMovement* movement;

		guard_direction dir;
		float app_time = 0.0f;
		int animation_counter = 0;
	};
}

