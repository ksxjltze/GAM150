#pragma once
#include "Image.h"

namespace TempTeam
{
	class Tile
	{
	public:
		Tile();
		void Init(Image* image);
		void Update();
		void Draw(AEVec2 mapPos, float width, float height);
		void Exit();
	private:
		Image* image;
		AEVec2 position;
	};
}