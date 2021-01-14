#pragma once
#include <vector>
#include "Tile.h"
#include "GameObject.h"
#include "Drag.h"

namespace TempTeam
{
	class Tilemap : public GameObject
	{
	public:
		void Init();
		void Update();
		void Draw();
		void Exit();
	private:
		std::vector<std::vector<Tile>> tiles;
		Image tileImage;
		float tileWidth, tileHeight;
		Drag drag;
	};
}