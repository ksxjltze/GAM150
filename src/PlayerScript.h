#pragma once
#include "ScriptComponent.h"
#include "Listener.h"
#include "PrimaryMovementController.h"
#include "ImageComponent.h"
#include "StealthWalk.h"
#include "Text.h"

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
		bool isInvisible();

		void Debug_Reset();

		inline bool GetDetected() const { return detected; }

	private:
		GameObject* client = nullptr;
		PrimaryMovementController* rb_controller;
		StealthWalk* stealth;
		Text* text;

		float range;
		bool gameover = false;
		bool playerEscaped = false;
		bool clientEscaped = false;
		bool detected = false;
	};
}