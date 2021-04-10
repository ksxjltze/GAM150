/******************************************************************************/
/*!
\title		Captain Stealth
\file		UIComponent.h
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

#pragma once
#include "ComponentCRTP.h"
#include "Sprite.h"
#include "GraphicsManager.h"

namespace StarBangBang
{
	class UIComponent : public Component<UIComponent>
	{
	public:
		UIComponent(GameObject* gameObject, GraphicsManager&, bool rescale = true);
		UIComponent(GameObject* gameObject, Sprite s, GraphicsManager&, bool rescale = true);
		void SetColor(Color c);
		void Start();
		void Update();
		void SetTransparency(float a);
		void Draw();
		bool rescale;	//Whether the object is rescaled during fullscreen.
	private:
		float transparency{ 1.0f };
		Sprite sprite;
		GraphicsManager& gfxMgr;
	};
}