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

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/

#include "ImageComponent.h"
#include "Utils.h"

/*!*************************************************************************
 * \brief
 * Component Constructor.
 * Attaches the component to a game object.
 * \param gameObject
 * GameObject to attach to.
***************************************************************************/
StarBangBang::ImageComponent::ImageComponent(GameObject* gameObject) : Component (gameObject)
{
}

/*!*************************************************************************
 * \brief
 * Component Constructor.
 * Attaches the component to a game object and sets the Image sprite.
 * \param gameObject
 * GameObject to attach to.
 * \param sprite
 * Sprite to use for drawing.
***************************************************************************/
StarBangBang::ImageComponent::ImageComponent(GameObject* gameObject, Sprite sprite) : sprite(sprite), Component(gameObject)
{
	
}

/*!*************************************************************************
 * \brief
 * Component Constructor.
 * Attaches the component to a game object and sets the Image sprite.
 * \param gameObject
 * GameObject to attach to.
 * \param mesh
 * Mesh to use for drawing.
 * \param texture
 * Texture to use for drawing.
***************************************************************************/
StarBangBang::ImageComponent::ImageComponent(GameObject* gameObject, AEGfxVertexList* mesh, AEGfxTexture* texture) : Component (gameObject)
{
	sprite.mesh = mesh;
	sprite.texture = texture;
}

/*!*************************************************************************
 * \brief
 * Sets the current texture.
 * \param texture
 * Texture to use for drawing.
***************************************************************************/
void StarBangBang::ImageComponent::SetTexture(AEGfxTexture* texture)
{
	sprite.texture = texture;
}

/*!*************************************************************************
 * \brief
 * Sets the current mesh.
 * \param mesh
 * Mesh to use for drawing.
***************************************************************************/
void StarBangBang::ImageComponent::SetMesh(AEGfxVertexList* mesh)
{
	sprite.mesh = mesh;
}

/*!*************************************************************************
 * \brief
 * Sets the current color.
 * \param c
 * Color to tint during drawing.
***************************************************************************/
void StarBangBang::ImageComponent::SetColor(Color c)
{
	sprite.color = c;
}

/*!*************************************************************************
 * \brief
 * Sets the current transparency.
 * \param alpha
 * Transparency value to draw with.
***************************************************************************/
void StarBangBang::ImageComponent::SetTransparency(float alpha)
{
	transparency = alpha;
}


/*!*************************************************************************
 * \brief
 * Draw function. Called once per frame.
 * Invokes the Graphics System to Draw the sprite.
***************************************************************************/
void StarBangBang::ImageComponent::Draw()
{
	Draw(gameObject->transform.position);
}

/*!*************************************************************************
 * \brief
 * Draw function. Called once per frame.
 * Invokes the Graphics System to Draw the sprite.
 * \param pos
 * Position to draw at.
***************************************************************************/
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
