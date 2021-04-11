/******************************************************************************/
/*!
\title		Captain Stealth
\file		GameStateManager.cpp
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

#include "GameStateManager.h"
#include "BasicMeshShape.h"
#include "State.h"
#include <iostream>
#include "PathFinder.h"

namespace StarBangBang
{
	bool GameStateManager::isRunning = false;

	/*!*************************************************************************
	 * \brief
	 * Default Constructor. Initializes the state pointers to null.
	***************************************************************************/
	GameStateManager::GameStateManager() 
	{
		currentState = nullptr;
		prevState = nullptr;
		nextState = nullptr;
		stateChanged = false;
	}

	/*!*************************************************************************
	 * \brief
	 * Destructor. Unloads all game states and deletes them.
	***************************************************************************/
	GameStateManager::~GameStateManager()
	{
		if (currentState)
		{
			Unload();
		}

		for (Scene* scene : gameStateList)
		{
			delete scene;
		}
	}

	/*!*************************************************************************
	 * \brief
	 * Adds an existing game state to the game state list.
	 * \param state
	 * Pointer to the state to add.
	 * \return
	 * void
	***************************************************************************/
	void GameStateManager::AddGameState(Scene* state)
	{
		if (state)
			gameStateList.push_back(state);
	}

	/*!*************************************************************************
	 * \brief
	 * Sets the initial game state.
	 * \param state
	 * State to set.
	 * \return
	 * void
	***************************************************************************/
	void GameStateManager::SetInitialState(Scene* state)
	{
		currentState = state;
		stateChanged = true;
		isRunning = true;
	}

	/*!*************************************************************************
	 * \brief
	 * Sets the initial game state by ID.
	 * \param id
	 * Id of the game state to set.
	 * \return
	 * void
	***************************************************************************/
	void GameStateManager::SetInitialState(int id)
	{
		Scene* scene = GetGameState(id);
		if (scene)
		{
			currentState = scene;
			stateChanged = true;
			isRunning = true;
		}
	}

	/*!*************************************************************************
	 * \brief
	 * Gets a game state by its ID.
	 * \param id
	 * Id of the game state to find.
	 * \return
	 * Pointer to the game state that was found.
	 * Returns nullptr if not found.
	***************************************************************************/
	Scene* GameStateManager::GetGameState(int id)
	{
		for (Scene* state : gameStateList)
		{
if (state->getID() == id)
{
	return state;
}
		}

		std::cout << "Specified State does not exist!" << std::endl;
		return nullptr;
	}

	/*!*************************************************************************
	 * \brief
	 * Sets the next game state.
	 * \param state
	 * State to set.
	 * \return
	 * void
	***************************************************************************/
	void GameStateManager::SetNextGameState(Scene* state)
	{
		nextState = state;
		stateChanged = true;
	}

	/*!*************************************************************************
	 * \brief
	 * Sets the next game state by id.
	 * \param id
	 * ID of the state to set
	 * \return
	 * void
	***************************************************************************/
	void GameStateManager::SetNextGameState(int id)
	{
		Scene* scene = GetGameState(id);
		if (scene)
		{
			nextState = scene;
			stateChanged = true;
		}
	}

	/*!*************************************************************************
	 * \brief
	 * Sets the next game state to the next game state in the list.
	 * \return
	 * void
	***************************************************************************/
	void GameStateManager::SetNextGameState()
	{
		SetNextGameState(currentState->id + 1);
	}

	/*!*************************************************************************
	 * \brief
	 * Resets the current game state.
	 * \return
	 * void
	***************************************************************************/
	void GameStateManager::ResetGameState()
	{
		nextState = currentState;
		MessageBus::Reset();
		stateChanged = true;
	}

	/*!*************************************************************************
	 * \brief
	 * Reloads the current game state.
	 * \return
	 * void
	***************************************************************************/
	void GameStateManager::ReloadGameState()
	{
		currentState->Unload();
		currentState->Free();
		currentState->Load();
		currentState->Init();
	}

	/*!*************************************************************************
	 * \brief
	 * Updates the current game state and checks for game state changes.
	 * \return
	 * void
	***************************************************************************/
	void GameStateManager::Update()
	{
		if (currentState)
		{
			if (!isRunning)
			{
				currentState->Free();
				currentState->Unload();
				currentState = nullptr;
				nextState = nullptr;
				return;
			}

			if (stateChanged)
			{
				if (nextState != nullptr)
				{
					currentState->Free();
					if (nextState != currentState)
					{
						currentState->Unload();
					}

					prevState = currentState;
					currentState = nextState;
					nextState = nullptr;
					AEInputReset();
				}

				GRAPHICS::ResetCamera();

				if (currentState != prevState)
					currentState->Load();
				currentState->Init();
				currentState->Start();
				stateChanged = false;

			}
			currentState->Update();
			//PathFinder::GridDraw();
			currentState->Draw();
		}
		else
		{
			std::cout << "ERROR: State not found." << std::endl;
		}
	}

	/*!*************************************************************************
	 * \brief
	 * Unloads the current game state.
	 * \return
	 * void
	***************************************************************************/
	void GameStateManager::Unload()
	{
		currentState->Free();
		currentState->Unload();
	}

	/*!*************************************************************************
	 * \brief
	 * Exits the game, terminates the game loop.
	 * \return
	 * void
	***************************************************************************/
	void GameStateManager::ExitGame()
	{
		isRunning = false;
	}

	/*!*************************************************************************
	 * \brief
	 * Gets the current status of the game.
	 * \return
	 * True if the game is still running, false otherwise.
	***************************************************************************/
	bool GameStateManager::GetStatus()
	{
		return isRunning;
	}

}
