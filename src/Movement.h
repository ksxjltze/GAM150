#pragma once
#include "ScriptComponent.h"

namespace StarBangBang
{
	class Movement : public Script
	{
	public:
		Movement(GameObject* gameObject);
		void Start();
		void Update();
	};
}