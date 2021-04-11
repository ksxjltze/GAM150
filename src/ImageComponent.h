/******************************************************************************/
/*!
\title		Captain Stealth
\file		ImageComponent.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		ImageComponent component class.
			Responsible for drawing game objects.

			Interfaces with the Graphics system to render sprites onto the screen.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "ComponentCRTP.h"
#include "GraphicsManager.h"

namespace StarBangBang
{
	class ImageComponent : public Component<ImageComponent>
	{
	public:
		/*!*************************************************************************
		 * \brief 
		 * Component Constructor.
		 * Attaches the component to a game object.
		 * \param gameObject
		 * GameObject to attach to.
		***************************************************************************/
		ImageComponent(GameObject* gameObject);

		/*!*************************************************************************
		 * \brief 
		 * Component Constructor.
		 * Attaches the component to a game object and sets the Image sprite.
		 * \param gameObject
		 * GameObject to attach to.
		 * \param sprite
		 * Sprite to use for drawing.
		***************************************************************************/
		ImageComponent(GameObject* gameObject, Sprite sprite);

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
		ImageComponent(GameObject* gameObject, AEGfxVertexList* mesh, AEGfxTexture* texture);

		/*!*************************************************************************
		 * \brief 
		 * Sets the current sprite.
		 * \param s
		 * Sprite to use for drawing.
		***************************************************************************/
		void SetSprite(Sprite s) { sprite = s; }

		/*!*************************************************************************
		 * \brief 
		 * Sets the current texture.
		 * \param texture
		 * Texture to use for drawing.
		***************************************************************************/
		void SetTexture(AEGfxTexture* texture);

		/*!*************************************************************************
		 * \brief 
		 * Sets the current mesh.
		 * \param mesh
		 * Mesh to use for drawing.
		***************************************************************************/
		void SetMesh(AEGfxVertexList* mesh);

		/*!*************************************************************************
		 * \brief 
		 * Sets the current color.
		 * \param c
		 * Color to tint during drawing.
		***************************************************************************/
		void SetColor(Color c);

		/*!*************************************************************************
		 * \brief 
		 * Sets the current transparency.
		 * \param alpha
		 * Transparency value to draw with.
		***************************************************************************/
		void SetTransparency(float alpha);

		/*!*************************************************************************
		 * \brief 
		 * Gets the current sprite.
		 * \return 
		 * Sprite to be used for drawing.
		***************************************************************************/
		Sprite GetSprite() { return sprite; }

		/*!*************************************************************************
		 * \brief 
		 * Draw function. Called once per frame.
		 * Invokes the Graphics System to Draw the sprite.
		***************************************************************************/
		void Draw();

		/*!*************************************************************************
		 * \brief
		 * Draw function. Called once per frame.
		 * Invokes the Graphics System to Draw the sprite.
		 * \param pos
		 * Position to draw at.
		***************************************************************************/
		void Draw(AEVec2 pos);
	private:
		Sprite sprite;
		float transparency{ 1.0f };
	};
}