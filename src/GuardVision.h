#pragma once
#include "ScriptComponent.h"
#include "Detector.h"

namespace StarBangBang
{
	class GuardMovement;
	//class Detector;

	class GuardVision : public Script
	{
	public:
		GuardVision(GameObject* gameObject);

		void Start();
		void Update();

		void Idle();

		inline Detector* GetDetector() { return detector; }

	private:
		void FaceTowardsRotation();

		GuardMovement* movement;
		Detector* detector;

		float rotation;
		int prevRot, currRot;

		bool turn;
	};
}