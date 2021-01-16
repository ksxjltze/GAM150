#pragma once
#include <vector>
#include "Tile.h"
#include "GameObject.h"
#include "Drag.h"
#include "ColliderAABB.h"

namespace StarBangBang
{
	class Tilemap : public GameObject
	{
	public:
		void Init();
		void Update();
		void Draw();
		void Exit();
	private:
		ColliderAABB collider;
		std::vector<std::vector<Tile>> tiles;
		Image tileImage;
		float tileWidth, tileHeight;
		int mapWidth, mapHeight;
		Drag drag;
	};
}