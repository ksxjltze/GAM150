#pragma once
#include "ScriptComponent.h"

namespace StarBangBang
{
	class Detector;

	class SecurityCamera : public Script
	{
	public:
		SecurityCamera(GameObject* gameObject);

		void Start();
		void Update();
		void SetRotationMinMax(float _minRot, float _maxRot);

	private:
		float minRot, maxRot;
		Detector* detector;
	};
}