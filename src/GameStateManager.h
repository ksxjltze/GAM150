#pragma once
#include "State.h"
#include <vector>

namespace StarBangBang
{
	class GameStateManager
	{
	public:
		GameStateManager();
		~GameStateManager();

		template <class StateType>
		State* AddGameState()
		{
			State* newState = new StateType(this);
			gameStateList.push_back(newState);
			return newState;
		}
		void AddGameState(State* state);

		void SetInitialState(State* state);
		void SetNextGameState(State* state);
		void Update();
	private:
		bool stateChanged;
		State* prevState;
		State* currentState;
		std::vector<State*> gameStateList;
	};
}