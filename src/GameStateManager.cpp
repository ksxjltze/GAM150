#include "GameStateManager.h"
#include <iostream>

StarBangBang::GameStateManager::GameStateManager()
{
	currentState = nullptr;
	prevState = nullptr;
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
	prevState = currentState;
	currentState = state;
	stateChanged = true;
}

void StarBangBang::GameStateManager::Update()
{
	if (currentState)
	{
		if (stateChanged)
		{
			if (prevState != nullptr)
			{
				prevState->Unload();
				prevState->Free();
			}

			currentState->Load();
			currentState->Init();

			prevState = nullptr;
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
