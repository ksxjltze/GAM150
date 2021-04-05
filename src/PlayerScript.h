#pragma once
#include "ScriptComponent.h"
#include "Listener.h"
#include "PrimaryMovementController.h"
#include "ImageComponent.h"

namespace StarBangBang
{
	class PlayerScript : public Script, public Listener
	{
	public:
		PlayerScript(GameObject* obj);
		void Update();
		void onNotify(Event e);
		bool isGameOver();
		bool isWin();
		void Start();
		bool isInvisible() { return invisible; }

		void Debug_Reset();

		inline bool GetDetected() const { return detected; }

	private:
		GameObject* client = nullptr;
		PrimaryMovementController* rb_controller;
		ImageComponent* image;

		float timer;
		float cooldown;

		float range;
		bool invisible = false;
		bool gameover = false;
		bool playerEscaped = false;
		bool clientEscaped = false;
		bool detected = false;
	};
}