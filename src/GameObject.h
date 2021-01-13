#pragma once
#include "Transform.h"

namespace TempTeam
{
	class GameObject
	{
	public:
		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual void Exit() = 0;
		Transform transform;
	};
}