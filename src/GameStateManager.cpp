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
	GameStateManager::GameStateManager() : isRunning{ false }
	{
		currentState = nullptr;
		prevState = nullptr;
		nextState = nullptr;
		stateChanged = false;
	}

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

	void GameStateManager::AddGameState(Scene* state)
	{
		if (state)
			gameStateList.push_back(state);
	}

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


	void GameStateManager::SetInitialState(Scene* state)
	{
		currentState = state;
		stateChanged = true;
		isRunning = true;
	}

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

	void GameStateManager::SetNextGameState(Scene* state)
	{
		nextState = state;
		stateChanged = true;
	}

	void GameStateManager::SetNextGameState(int id)
	{
		Scene* scene = GetGameState(id);
		if (scene)
		{
			nextState = scene;
			stateChanged = true;
		}
	}

	void GameStateManager::SetNextGameState()
	{
		SetNextGameState(currentState->id + 1);
	}

	void GameStateManager::ResetGameState()
	{
		currentState->Free();
		currentState->Init();
	}

	void GameStateManager::ReloadGameState()
	{
		currentState->Unload();
		currentState->Free();
		currentState->Load();
		currentState->Init();
	}

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
					currentState->Unload();
					prevState = currentState;
					currentState = nextState;
					AEInputReset();
				}

				GRAPHICS::ResetCamera();
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

	void GameStateManager::Unload()
	{
		currentState->Free();
		currentState->Unload();
	}

	void GameStateManager::ExitGame()
	{
		isRunning = false;
	}

	bool GameStateManager::GetStatus()
	{
		return isRunning;
	}

}
