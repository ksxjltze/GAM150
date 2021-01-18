#pragma once
#include "Image.h"

namespace StarBangBang
{
	class Tile
	{
	public:
		Tile();
		void Init(Image* image, AEVec2 position);
		void Update();
		void Draw(AEVec2 mapPos, float width, float height);
		void Exit();
	private:
		Image* image;
		AEVec2 position;
	};
}