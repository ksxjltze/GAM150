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

		inline void SetRoomNum(unsigned int num) { roomNum = num; }
		inline unsigned int GetRoomNum() const { return roomNum; }

	private:
		unsigned int roomNum;
		float minRot, maxRot;
		float rotSpeed;
		Detector* detector;
		bool detected;
	};
}