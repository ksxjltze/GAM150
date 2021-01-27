#pragma once
#include "ComponentCRTP.h"
#include "GraphicsManager.h"

namespace StarBangBang
{
	class ImageComponent : public Component<ImageComponent>
	{
	public:
		ImageComponent(GameObject* gameObject, AEGfxVertexList* mesh, AEGfxTexture* texture);

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