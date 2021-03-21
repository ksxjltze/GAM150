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
		void Draw();

		void Init(float fov, float dist, GameObject* player, GameObject* client);
		void Rotate(float angle);

		void SpanVision(float minRot, float maxRot, float speed);

		inline void SetAngle(float angle) { rotationAngle = angle; }
		inline void SetFacingDir(const AEVec2& dir) { targetDir = dir; }
		inline bool DetectedPlayer() const { return detected; }
		inline float GetRotation() const { return rotationAngle; }

	private:
		void CheckForTargets(const AEVec2& _targetPos);

		float fieldOfView;
		float viewDist;
		float rotationAngle;

		bool atMaxRot;

		bool detected;

		AEVec2 defaultForward;
		AEVec2 targetDir;

		GameObject* target1, *target2;
	};
}