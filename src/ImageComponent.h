/******************************************************************************/
/*!
\title		Captain Stealth
\file		ImageComponent.h
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

#pragma once
#include "ComponentCRTP.h"
#include "GraphicsManager.h"

namespace StarBangBang
{
	class ImageComponent : public Component<ImageComponent>
	{
	public:
		ImageComponent(GameObject* gameObject);
		ImageComponent(GameObject* gameObject, Sprite sprite);
		ImageComponent(GameObject* gameObject, AEGfxVertexList* mesh, AEGfxTexture* texture);
		void SetSprite(Sprite s) { sprite = s; }
		void SetTexture(AEGfxTexture* texture);
		void SetMesh(AEGfxVertexList* mesh);
		void SetColor(Color c);
		void SetTransparency(float alpha);
		Sprite GetSprite() { return sprite; }

		void Draw();
		void Draw(AEVec2 pos);
	private:
		Sprite sprite;
		float transparency{ 1.0f };
	};
}