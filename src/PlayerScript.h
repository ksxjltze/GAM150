/******************************************************************************/
/*!
\title		Captain Stealth
\file		PlayerScript.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Player script. 
			Responsible for Player mechanics such as Stealth
			as well as controlling the win and lose conditions for the game.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

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

		float gameOverTimer;
	};
}