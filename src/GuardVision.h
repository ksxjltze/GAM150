#pragma once
#include "ScriptComponent.h"

namespace StarBangBang
{
	class GuardVision : public Script
	{
	public:
		GuardVision(GameObject* gameObject);

		void Start() {}
		void Update() {};
		void Scan();

		inline void SetPlayerAndClient(GameObject* _player, GameObject* _client) { player = _player; client = _client; }
		inline void SetDetected(bool _detected) { detected_player = _detected; }
		inline bool GetDetected() { return detected_player; }

	private:
		bool detected_player;
		GameObject* player;
		GameObject* client;
	};
}