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

		inline Detector* GetDetector() { return detector; }

	private:
		GuardMovement* movement;
		Detector* detector;

		float rotation;
	};
}