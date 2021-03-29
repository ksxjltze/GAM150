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
	private:
		Sprite sprite;
		float transparency{ 1.0f };
	};
}