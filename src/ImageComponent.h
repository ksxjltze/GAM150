#pragma once
#include "Component.h"
#include "GraphicsManager.h"

namespace StarBangBang
{
	class ImageComponent : public Component
	{
	public:
		ImageComponent(GameObject* gameObject, AEGfxVertexList* mesh, AEGfxTexture* texture);
		void Draw();
	private:
		AEGfxVertexList* mesh;
		AEGfxTexture* texture;
	};
}