#pragma once
#include "ComponentCRTP.h"

namespace StarBangBang
{
	class CameraComponent : public ComponentCRTP<CameraComponent>
	{
	public:
		CameraComponent(GameObject* gameObject);
		void Update();
		AEVec2 position;
	};
}