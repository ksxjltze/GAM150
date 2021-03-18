#pragma once
#include "ScriptComponent.h"

namespace StarBangBang
{
	class Detector;

	class SecurityCamera : public Script
	{
	private:
		const float ROT_SPEED = 50.f;

	public:
		SecurityCamera(GameObject* gameObject);

		void Start();
		void Update();
		void SetRotationMinMax(float _minRot, float _maxRot);

	private:
		bool atMaxRot;
		float minRot, maxRot;
		float rotation;
		Detector* detector;
	};
}