#include "GameStateManager.h"
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
	currentState->Free();
	currentState->Unload();
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
	//will probably change later
	for (State* state : gameStateList)
	{
		if (state->getID() == id)
		{
			nextState = state;
		}
	}
	stateChanged = true;
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
