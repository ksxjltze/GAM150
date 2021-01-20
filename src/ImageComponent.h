#pragma once
#include "Component.h"
#include "GraphicsManager.h"

namespace StarBangBang
{
	class ImageComponent : public Component
	{
	public:
		ImageComponent(GameObject* gameObject, AEGfxVertexList* mesh, AEGfxTexture* texture);
		Component* Clone(GameObject* gameObject, Component* component);
		inline void SetTexture(AEGfxTexture* texture) { this->texture = texture; }
		inline void SetMesh(AEGfxVertexList* mesh) { this->mesh = mesh; }
		inline AEGfxTexture* GetTexture() { return texture; }
		inline AEGfxVertexList* GetMesh() { return mesh; }
		void Draw();
		const static int id = 1;
	private:
		AEGfxVertexList* mesh;
		AEGfxTexture* texture;
	};
}