/******************************************************************************/
/*!
\title		Captain Stealth
\file		GameStateManager.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Game State Manager class.
			Is responsible for managing game states/scenes.
			Updates game states once per frame and handles calls
			to change game states.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include <vector>

namespace StarBangBang
{
	class Scene;
	class GameStateManager
	{
	public:
		/*!*************************************************************************
		 * \brief 
		 * Default Constructor. Initializes the state pointers to null.
		***************************************************************************/
		GameStateManager();

		/*!*************************************************************************
		 * \brief 
		 * Destructor. Unloads all game states and deletes them.
		***************************************************************************/
		~GameStateManager();

		/*!*************************************************************************
		 * \brief 
		 * Creates and adds a game state to the game state list.
		 * \return 
		 * Pointer to the state that was added.
		***************************************************************************/
		template <class StateType>
		Scene* AddGameState()
		{
			Scene* newState = new StateType((int)gameStateList.size(), *this);
			gameStateList.push_back(newState);
			return newState;
		}

		/*!*************************************************************************
		 * \brief
		 * Creates and adds a game state to the game state list.
		 * \param
		 * ID of the game state to add.
		 * \return
		 * Pointer to the state that was added.
		***************************************************************************/
		template <class StateType>
		Scene* AddGameState(int id)
		{
			Scene* newState = new StateType(id, *this);
			gameStateList.push_back(newState);
			return newState;
		}

		/*!*************************************************************************
		 * \brief 
		 * Adds an existing game state to the game state list.
		 * \param state
		 * Pointer to the state to add.
		 * \return
		 * void
		***************************************************************************/
		void AddGameState(Scene* state);

		/*!*************************************************************************
		 * \brief 
		 * Sets the initial game state.
		 * \param state
		 * State to set.
		 * \return
		 * void
		***************************************************************************/
		void SetInitialState(Scene* state);

		/*!*************************************************************************
		 * \brief 
		 * Sets the initial game state by ID.
		 * \param id
		 * Id of the game state to set.
		 * \return
		 * void
		***************************************************************************/
		void SetInitialState(int id);

		/*!*************************************************************************
		 * \brief 
		 * Gets a game state by its ID.
		 * \param id
		 * Id of the game state to find.
		 * \return 
		 * Pointer to the game state that was found.
		 * Returns nullptr if not found.
		***************************************************************************/
		Scene* GetGameState(int id);

		/*!*************************************************************************
		 * \brief 
		 * Sets the next game state.
		 * \param state
		 * State to set.
		 * \return
		 * void
		***************************************************************************/
		void SetNextGameState(Scene* state);

		/*!*************************************************************************
		 * \brief 
		 * Sets the next game state by id.
		 * \param id
		 * ID of the state to set
		 * \return
		 * void
		***************************************************************************/
		void SetNextGameState(int id);

		/*!*************************************************************************
		 * \brief 
		 * Sets the next game state to the next game state in the list.
		 * \return
		 * void
		***************************************************************************/
		void SetNextGameState();

		/*!*************************************************************************
		 * \brief 
		 * Resets the current game state.
		 * \return
		 * void
		***************************************************************************/
		void ResetGameState();

		/*!*************************************************************************
		 * \brief 
		 * Reloads the current game state.
		 * \return
		 * void
		***************************************************************************/
		void ReloadGameState();

		/*!*************************************************************************
		 * \brief 
		 * Updates the current game state and checks for game state changes.
		 * \return
		 * void
		***************************************************************************/
		void Update();

		/*!*************************************************************************
		 * \brief 
		 * Unloads the current game state.
		 * \return
		 * void
		***************************************************************************/
		void Unload();

		/*!*************************************************************************
		 * \brief 
		 * Exits the game, terminates the game loop.
		 * \return
		 * void
		***************************************************************************/
		void ExitGame();

		/*!*************************************************************************
		 * \brief 
		 * Gets the current status of the game.
		 * \return 
		 * True if the game is still running, false otherwise.
		***************************************************************************/
		bool GetStatus();
	private:
		bool isRunning;
		bool stateChanged;
		Scene* prevState;
		Scene* currentState;
		Scene* nextState;
		std::vector<Scene*> gameStateList;
	};
}