#pragma once
#include "Component.h"

namespace StarBangBang
{
	class DragComponent : public Component
	{
	public:
		DragComponent(GameObject* gameObject);
		void Update();
		const static int id = 2;
	private:
		bool enabled;
	};
}