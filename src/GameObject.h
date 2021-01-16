#pragma once
#include "Transform.h"

namespace TempTeam
{
	class GameObject
	{
	public:
		virtual void Init() {};
		virtual void Update() {};
		virtual void Draw() {};
		virtual void Exit() {};
		Transform transform;
		float width = 0, height = 0;
	};
}