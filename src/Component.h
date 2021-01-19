#pragma once
#include "GameObject.h"

namespace StarBangBang
{
	class Component
	{
	public:
		virtual void Update() {};
		int id { 0 };
	protected:
		GameObject* gameObject { nullptr };
	};
}