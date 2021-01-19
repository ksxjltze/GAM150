#pragma once
#include "GameObject.h"

namespace StarBangBang
{
	class Component
	{
	public:
		int id { 0 };
	protected:
		GameObject* gameObject;
	};
}