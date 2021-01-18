#pragma once
#include "Component.h"

namespace StarBangBang
{
	class DragComponent : public Component
	{
	public:
		DragComponent(GameObject* gameObject);
		void Update(AEVec2 mousePos);
	private:
		bool enabled;
	};
}