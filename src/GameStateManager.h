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
		void ResetGameState();
		void ReloadGameState();
		void Update();
		void ExitGame();
	private:
		bool stateChanged;
		Scene* prevState;
		Scene* currentState;
		Scene* nextState;
		std::vector<Scene*> gameStateList;
	};
}