/******************************************************************************/
/*!
\title		Captain Stealth
\file		ImageComponent.cpp
\author 	Lee Jia Keat
\par    	email: l.jiakeat@digipen.edu
\date   	April 09, 2021
\brief		ImageComponent component class.
			Responsible for drawing game objects.

			Interfaces with the Graphics system to render sprites onto the screen.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#include "ImageComponent.h"
#include "Utils.h"

StarBangBang::ImageComponent::ImageComponent(GameObject* gameObject) : Component (gameObject)
{
}

StarBangBang::ImageComponent::ImageComponent(GameObject* gameObject, Sprite sprite) : sprite(sprite), Component(gameObject)
{
	
}

StarBangBang::ImageComponent::ImageComponent(GameObject* gameObject, AEGfxVertexList* mesh, AEGfxTexture* texture) : Component (gameObject)
{
	sprite.mesh = mesh;
	sprite.texture = texture;
}

void StarBangBang::ImageComponent::SetTexture(AEGfxTexture* texture)
{
	sprite.texture = texture;
}

void StarBangBang::ImageComponent::SetMesh(AEGfxVertexList* mesh)
{
	sprite.mesh = mesh;
}

void StarBangBang::ImageComponent::SetColor(Color c)
{
	sprite.color = c;
}

void StarBangBang::ImageComponent::SetTransparency(float alpha)
{
	transparency = alpha;
}

void StarBangBang::ImageComponent::Draw()
{
	Draw(gameObject->transform.position);
}

void StarBangBang::ImageComponent::Draw(AEVec2 pos)
{
	if (gameObject->active && gameObject->visible)
	{
		if (sprite.mesh && sprite.texture)
		{
			GRAPHICS::DrawImage(sprite.mesh, sprite.texture, sprite.color, pos, gameObject->transform.scale, gameObject->transform.rotation, transparency);

		}
	}
}
