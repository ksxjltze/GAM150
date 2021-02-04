#pragma once
#include "State.h"
#include "GameStateManager.h"
#include "Sprite.h"
#include "Grid.h"

namespace StarBangBang
{
	class LevelEditor : public Scene
	{
	public:
		LevelEditor(int id, GameStateManager& manager);
		void Load();
		void Init();
		void Update();
		void Draw();
		void Free();
		void Unload();
	private:
		float tileWidth, tileHeight;
		std::map<std::string, Sprite> palette;
		std::map<Node*, GameObject*> tileObjects;
		//std::vector<GameObject*> tileObjects;
		//std::vector<std::vector<AEVec2>> grid;
		Grid grid;
	};
}