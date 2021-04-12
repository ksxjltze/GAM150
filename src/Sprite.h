/******************************************************************************/
/*!
\title		Captain Stealth
\file		Sprite.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Sprite class.
			Contains a texture and a mesh.

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/

#pragma once
#include "AEEngine.h"
#include "Color.h"

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
		Color color;
	};
}