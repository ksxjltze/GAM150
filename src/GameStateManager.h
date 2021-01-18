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