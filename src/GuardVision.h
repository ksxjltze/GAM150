#pragma once
#include "ScriptComponent.h"

namespace StarBangBang
{
	class GuardMovement;
	class Detector;

	class GuardVision : public Script
	{
	public:
		GuardVision(GameObject* gameObject);

		void Start();
		void Update();

		void OnEnterIdle();
		void Idle();

		void OnEnterPatrol();
		void OnEnterDistracted();
		void OnEnterChase();

		inline Detector* GetDetector() { return detector; }
		inline void SetRotationSpeed(float speed) { rotSpeed = speed; }

	private:
		void FaceTowardsRotation();

		GuardMovement* movement;
		Detector* detector;

		float rotation;
		float rotSpeed;
		float idleDuration;
		int prevRot, currRot;

		bool turn;
	};
}