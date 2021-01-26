#include "GameStateManager.h"
#include "BasicMeshShape.h"
#include <iostream>

StarBangBang::GameStateManager::GameStateManager()
{
	currentState = nullptr;
	prevState = nullptr;
	nextState = nullptr;
	stateChanged = false;
}

StarBangBang::GameStateManager::~GameStateManager()
{
	if (currentState)
	{
		ExitGame();
	}
}

void StarBangBang::GameStateManager::AddGameState(State* state)
{
	if (state)
		gameStateList.push_back(state);
}

void StarBangBang::GameStateManager::SetInitialState(State* state)
{
	currentState = state;
	stateChanged = true;
}

void StarBangBang::GameStateManager::SetNextGameState(State* state)
{
	nextState = state;
	stateChanged = true;
}

void StarBangBang::GameStateManager::SetNextGameState(int id)
{
	for (State* state : gameStateList)
	{
		if (state->getID() == id)
		{
			nextState = state;
		}
	}
	stateChanged = true;
}

void StarBangBang::GameStateManager::ResetGameState()
{
	currentState->Free();
	currentState->Init();
}

void StarBangBang::GameStateManager::ReloadGameState()
{
	currentState->Unload();
	currentState->Free();
	currentState->Load();
	currentState->Init();
}

void StarBangBang::GameStateManager::Update()
{
	if (currentState)
	{
		if (stateChanged)
		{
			if (nextState != nullptr)
			{
				currentState->Unload();
				currentState->Free();
				prevState = currentState;
				currentState = nextState;
			}
			currentState->Load();
			currentState->Init();
			stateChanged = false;

		}
		currentState->Update();
		currentState->Draw();

	}
	else
	{
		std::cout << "ERROR: State not found." << std::endl;
	}
}

void StarBangBang::GameStateManager::ExitGame()
{
	currentState->Unload();
	currentState->Free();
	//free all unit meshes built
	StarBangBang::FreeUnitMeshes();
	currentState = nullptr;
	nextState = nullptr;
}
