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
		inline void SetRotSpeed(float _speed) { rotSpeed = _speed; }

	private:
		float minRot, maxRot;
		float rotSpeed;
		Detector* detector;
	};
}