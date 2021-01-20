#pragma once
#include "AEEngine.h"

namespace StarBangBang
{
	struct Sprite
	{
		Sprite() { texture = nullptr; mesh = nullptr; };
		AEGfxTexture* texture;
		AEGfxVertexList* mesh;
	};
}