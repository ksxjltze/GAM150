#pragma once
#include "ScriptComponent.h"

namespace StarBangBang
{
	class GuardAnim : public Script
	{
	public:
		GuardAnim(GameObject* gameObject);
		void Start();
		void Update();
	};
}

