#pragma once
#include "Collider.h"
#include "Transform.h"

namespace StarBangBang
{
	class ColliderAABB : public Collider
	{
	public:
		void Init(float width, float height);
		void OnEnter();
		void OnStay();
		void OnExit();
		float width = 0, height = 0;
	};
}