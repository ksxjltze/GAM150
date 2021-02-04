#pragma once
#include <vector>

namespace StarBangBang
{
	class State;
	class GameStateManager
	{
	public:
		GameStateManager();
		~GameStateManager();

		template <class StateType>
		State* AddGameState()
		{
			State* newState = new StateType((int)gameStateList.size(), *this);
			gameStateList.push_back(newState);
			return newState;
		}

		template <class StateType>
		State* AddGameState(int id)
		{
			State* newState = new StateType(id, *this);
			gameStateList.push_back(newState);
			return newState;
		}

		void AddGameState(State* state);

		void SetInitialState(State* state);
		void SetNextGameState(State* state);
		void SetNextGameState(int id);
		void ResetGameState();
		void ReloadGameState();
		void Update();
		void ExitGame();
	private:
		bool stateChanged;
		State* prevState;
		State* currentState;
		State* nextState;
		std::vector<State*> gameStateList;
	};
}