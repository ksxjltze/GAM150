#pragma once
#include "Collider.h"
#include "Transform.h"

namespace TempTeam
{
	class ColliderAABB : public Collider
	{
	public:
		void Init(float width, float height);
		void OnEnter();
		void OnStay();
		void OnExit();
		float width, height;
	};
}