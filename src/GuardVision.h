#pragma once
#include "ScriptComponent.h"
#include "Detector.h"

namespace StarBangBang
{
	class GuardMovement;

	class GuardVision : public Script
	{
	public:
		GuardVision(GameObject* gameObject);

		void Start();
		void Update();

		inline void SetPlayerAndClient(GameObject* _player, GameObject* _client) { player = _player; client = _client; }
		inline void SetDetected(bool _detected) { detected_player = _detected; }
		inline bool GetDetected() { return detected_player; }

	private:
		bool detected_player;
		float fieldOfView;
		float viewDist;
		float visionRot = 0.f;

		GameObject* player;
		GameObject* client;

		GuardMovement* movement;

		Detector* detector;
	};
}