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

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
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
		/*!*************************************************************************
		 * \brief 
		 * Script constructor.
		 * Attaches the script to a game object
		 * \param obj
		 * GameObject to attach to.
		***************************************************************************/
		PlayerScript(GameObject* obj);

		/*!*************************************************************************
		 * \brief 
		 * Start.
		 * \return 
		 * void
		***************************************************************************/
		void Start();
		
		/*!*************************************************************************
		 * \brief 
		 * Updates the player's cooldown and ability timers.
		 * Checks if the game is over or if the player has won.
		 * \return
		 * void
		***************************************************************************/
		void Update();

		/*!*************************************************************************
		 * \brief
		 * Listener callback. Invoked when an event is received from the Message Bus.
		 * Listens for events: CAUGHT_BY_CAMERA, GAME_OVER, DETECTED,
		 *					   PLAYER_COLLISION and COLLISION.
		 * \param e Event data.
		***************************************************************************/
		void onNotify(Event e);

		/*!*************************************************************************
		 * \brief 
		 * Determines if the game is over.
		 * \return 
		 * True if the conditions for game over are met,
		 * false otherwise.
		***************************************************************************/
		bool isGameOver();

		/*!*************************************************************************
		 * \brief 
		 * Determines if the game is won.
		 * \return 
		 * True if the conditions for winning are met,
		 * false otherwise.
		***************************************************************************/
		bool isWin();

		/*!*************************************************************************
		 * \brief 
		 * Determines if the player is invisible.
		 * \return 
		 * False if player is visible, true otherwise.
		***************************************************************************/
		bool isInvisible();

		/*!*************************************************************************
		 * \brief 
		 * Accessor.
		 * \return 
		 * True if player has escaped.
		***************************************************************************/
		bool isPlayerEscaped() { return playerEscaped; }

		/*!*************************************************************************
		 * \brief
		 * Accessor.
		 * \return
		 * True if client has escaped.
		***************************************************************************/
		bool isClientEscaped() { return clientEscaped; }

		/*!*************************************************************************
		 * \brief
		 * Resets the game over condition.
		 * \return
		 * void
		***************************************************************************/
		void Debug_Reset();

		/*!*************************************************************************
		 * \brief 
		 * Accessor.
		 * \return
		 * True if either player or client have been detected.
		***************************************************************************/
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