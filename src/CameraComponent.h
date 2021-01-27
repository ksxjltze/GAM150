#pragma once
#include "ComponentCRTP.h"

namespace StarBangBang
{
	class CameraComponent : public Component<CameraComponent>
	{
	public:
		CameraComponent(GameObject* gameObject);
		void Update();
		AEVec2 position;
	};
}