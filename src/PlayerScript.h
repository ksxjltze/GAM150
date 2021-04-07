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
		void Start();
		void Update();
		void onNotify(Event e);
		bool isGameOver();
		bool isWin();
		bool isInvisible();
		bool isPlayerEscaped() { return playerEscaped; }
		bool isClientEscaped() { return clientEscaped; }

		void Debug_Reset();

		inline bool GetDetected() const { return detected; }

	private:
		GameObject* client = nullptr;
		PrimaryMovementController* rb_controller;
		StealthWalk* stealth;
		Text* text;

		bool gameover = false;
		bool playerHidden = false;
		bool clientHidden = false;
		bool playerEscaped = false;
		bool clientEscaped = false;
		bool detected = false;
	};
}