#pragma once
#include "AEEngine.h"

namespace StarBangBang
{
	struct Sprite
	{
		Sprite() { texture = nullptr; mesh = nullptr; };
		Sprite(AEGfxTexture* texture, AEGfxVertexList* mesh)
		{
			this->texture = texture;
			this->mesh = mesh;
		}
		AEGfxTexture* texture;
		AEGfxVertexList* mesh;
	};
}