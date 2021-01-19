#pragma once
#include "Transform.h"

namespace StarBangBang
{
	class GameObject
	{
	public:
		Transform transform;
		float width = 0, height = 0;
		bool active = true;
		GameObject* parent = nullptr;
	};
}