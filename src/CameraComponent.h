#pragma once
#include "ComponentCRTP.h"

namespace StarBangBang
{
	class CameraComponent : public Component<CameraComponent>
	{
	public:
		CameraComponent(GameObject* gameObject);
		void LateUpdate();
		AEVec2 position;
		float scale;
		float scaleFactor;
		void SetTarget(GameObject* obj);
		GameObject* GetTarget();
	private:
		GameObject* target;

	};
}