#pragma once
#include "ComponentCRTP.h"
#include "GraphicsManager.h"

namespace StarBangBang
{
	class ImageComponent : public Component
	{
	public:
		ImageComponent(GameObject* gameObject, AEGfxVertexList* mesh, AEGfxTexture* texture);
		Component* Clone(GameObject* gameObject, Component* component);

		inline void SetTexture(AEGfxTexture* texturePtr) { texture = texturePtr; }
		inline void SetMesh(AEGfxVertexList* meshPtr) { mesh = meshPtr; }

		inline AEGfxTexture* GetTexture() { return texture; }
		inline AEGfxVertexList* GetMesh() { return mesh; }

		void Draw();
	private:
		AEGfxVertexList* mesh;
		AEGfxTexture* texture;
	};
}