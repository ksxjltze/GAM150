#pragma once
#include "ScriptComponent.h"

namespace StarBangBang
{
	class Detector : public Script
	{
	public:
		Detector(GameObject* gameObject);

		void Start() {}
		void Update();

		void Init(float fov, float dist, bool fixedPos, GameObject* target);
		void Rotate(float angle);
		void DrawVision(const AEVec2& pos);

		inline void SetAngle(float angle) { rotationAngle = angle; }
		inline void SetFacingDir(const AEVec2& dir) { targetDir = dir; }
		inline bool DetectedPlayer() const { return detected; }

	private:
		void CheckForTargets();

		float fieldOfView;
		float viewDist;
		float rotationAngle;

		bool detected;
		bool isFixedPos;

		AEVec2 defaultForward;
		AEVec2 targetDir;

		GameObject* targetGO;
	};
}