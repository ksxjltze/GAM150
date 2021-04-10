/******************************************************************************/
/*!
\title		Captain Stealth
\file		GameStateManager.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat@digipen.edu
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
		GameStateManager();
		~GameStateManager();

		template <class StateType>
		Scene* AddGameState()
		{
			Scene* newState = new StateType((int)gameStateList.size(), *this);
			gameStateList.push_back(newState);
			return newState;
		}

		template <class StateType>
		Scene* AddGameState(int id)
		{
			Scene* newState = new StateType(id, *this);
			gameStateList.push_back(newState);
			return newState;
		}

		void AddGameState(Scene* state);

		void SetInitialState(Scene* state);
		void SetInitialState(int id);
		Scene* GetGameState(int id);
		void SetNextGameState(Scene* state);
		void SetNextGameState(int id);
		void SetNextGameState();
		void ResetGameState();
		void ReloadGameState();
		void Update();
		void Unload();
		void ExitGame();
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