#include "GameStateManager.h"
#include "BasicMeshShape.h"
#include "State.h"
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

	for (Scene* scene : gameStateList)
	{
		delete scene;
	}
}

void StarBangBang::GameStateManager::AddGameState(Scene* state)
{
	if (state)
		gameStateList.push_back(state);
}

void StarBangBang::GameStateManager::SetInitialState(Scene* state)
{
	currentState = state;
	stateChanged = true;
}

void StarBangBang::GameStateManager::SetNextGameState(Scene* state)
{
	nextState = state;
	stateChanged = true;
}

void StarBangBang::GameStateManager::SetNextGameState(int id)
{
	bool found = false;
	for (Scene* state : gameStateList)
	{
		if (state->getID() == id)
		{
			found = true;
			nextState = state;
			break;
		}
	}

	if (found)
	{
		stateChanged = true;
		return;
	}
	else
		std::cout << "Specified State does not exist!" << std::endl;
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
				currentState->Free();
				currentState->Unload();
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
	currentState->Free();
	//free all unit meshes built
	currentState->Unload();
	currentState = nullptr;
	nextState = nullptr;
}
