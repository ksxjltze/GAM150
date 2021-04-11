/******************************************************************************/
/*!
\title		Captain Stealth
\file		UIComponent.cpp
\author 	Lee Jia Keat
\par    	email: l.jiakeat@digipen.edu
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

#include "UIComponent.h"

namespace StarBangBang
{
	const static float FULLSCREEN_SCALE = 2.0f;

	/*!*************************************************************************
	 * \brief
	 * Component Constructor.
	 * Attaches the component to a game object.
	 * \param gameObject
	 * GameObject to attach to.
	 * \param gfx
	 * GraphicsManager reference.
	 * \param rescale
	 * True to rescale during full screen, false to let AlphaEngine scale it ins
	***************************************************************************/
	UIComponent::UIComponent(GameObject* gameObject, GraphicsManager& gfx, bool rescale) : Component(gameObject), transparency{1.0f}, gfxMgr{ gfx }, rescale{ rescale }
	{

	}

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
	UIComponent::UIComponent(GameObject* gameObject, Sprite uiSprite, GraphicsManager& gfx, bool rescale) : Component(gameObject), transparency{ 1.0f } ,sprite{ uiSprite }, gfxMgr{ gfx }, rescale{ rescale }
	{

	}

	/*!*************************************************************************
	 * \brief
	 * Sets the color of the sprite.
	 * \param spriteColor
	***************************************************************************/
	void UIComponent::SetColor(Color spriteColor)
	{
		sprite.color = spriteColor;
	}

	/*!*************************************************************************
	 * \brief
	 * Start function. Called once at the start of the scene.
	***************************************************************************/
	void UIComponent::Start()
	{

	}

	/*!*************************************************************************
	 * \brief
	 * Update function. Called once every frame.
	***************************************************************************/
	void UIComponent::Update()
	{

	}

	/*!*************************************************************************
	 * \brief
	 * Set the transparency of the object.
	 * \param alpha
	 * Transparency value.
	***************************************************************************/
	void UIComponent::SetTransparency(float alpha)
	{
		transparency = alpha;
	}

	/*!*************************************************************************
	 * \brief
	 * Draw function. Called once every frame.
	***************************************************************************/
	void UIComponent::Draw()
	{
		if (gameObject->active)
		{
			//AEGfxSetTransparency(transparency);

			AEVec2 scale = gameObject->transform.scale;

			if (sprite.texture)
				GRAPHICS::DrawOverlay(gfxMgr.GetMesh(), sprite.texture, scale, gameObject->transform.position, sprite.color, rescale, transparency);
			else
				GRAPHICS::DrawOverlay(gfxMgr.GetMesh(), nullptr, scale, gameObject->transform.position, sprite.color, rescale, transparency);
			AEGfxSetTransparency(1.0f);

		}
	}

}