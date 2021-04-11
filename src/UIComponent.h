/******************************************************************************/
/*!
\title		Captain Stealth
\file		UIComponent.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		UIComponent class.
			Is responsible for drawing UI objects onto the screen.
			Is similar to the ImageComponent class, except that it can ignore
			the Camera and does not require a sprite.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "ComponentCRTP.h"
#include "Sprite.h"
#include "GraphicsManager.h"

namespace StarBangBang
{
	class UIComponent : public Component<UIComponent>
	{
	public:
		/*!*************************************************************************
		 * \brief 
		 * Component Constructor.
		 * Attaches the component to a game object.
		 * \param gameObject
		 * GameObject to attach to.
		 * \param gfx
		 * GraphicsManager reference.
		 * \param rescale
		 * True to rescale during full screen, false to let AlphaEngine scale it instead.
		***************************************************************************/
		UIComponent(GameObject* gameObject, GraphicsManager& gfx, bool rescale = true);

		/*!*************************************************************************
		 * \brief
		 * Component Constructor.
		 * Attaches the component to a game object.
		 * \param gameObject
		 * GameObject to attach to.
		 * \param uiSprite
		 * Sprite to use for drawing.
		 * \param gfx
		 * GraphicsManager reference.
		 * \param rescale
		 * True to rescale during full screen, false to let AlphaEngine scale it instead.
		***************************************************************************/
		UIComponent(GameObject* gameObject, Sprite uiSprite, GraphicsManager& gfx, bool rescale = true);

		/*!*************************************************************************
		 * \brief 
		 * Sets the color of the sprite.
		 * \param spriteColor
		***************************************************************************/
		void SetColor(Color spriteColor);

		/*!*************************************************************************
		 * \brief 
		 * Start function. Called once at the start of the scene.
		***************************************************************************/
		void Start();

		/*!*************************************************************************
		 * \brief 
		 * Update function. Called once every frame.
		***************************************************************************/
		void Update();

		/*!*************************************************************************
		 * \brief 
		 * Set the transparency of the object.
		 * \param alpha
		 * Transparency value.
		***************************************************************************/
		void SetTransparency(float alpha);

		/*!*************************************************************************
		 * \brief 
		 * Draw function. Called once every frame.
		***************************************************************************/
		void Draw();

		bool rescale;	//Whether the object is rescaled during full screen.
	private:
		float transparency{ 1.0f };
		Sprite sprite;
		GraphicsManager& gfxMgr;
	};
}