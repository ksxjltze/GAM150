#pragma once
#include "ScriptComponent.h"
#include "Listener.h"
#include "PrimaryMovementController.h"
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

		void Debug_Reset();

		inline bool GetDetected() const { return detected; }

	private:
		GameObject* client = nullptr;
		PrimaryMovementController* rb_controller;
		float range;
		bool gameover = false;
		bool playerEscaped = false;
		bool clientEscaped = false;
		bool detected = false;
	};
}