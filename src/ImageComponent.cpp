#include "ImageComponent.h"
#include "Utils.h"

StarBangBang::ImageComponent::ImageComponent(GameObject* gameObject) : Component (gameObject)
{
}

StarBangBang::ImageComponent::ImageComponent(GameObject* gameObject, Sprite sprite) : sprite(sprite), Component(gameObject)
{
	
}

StarBangBang::ImageComponent::ImageComponent(GameObject* gameObject, AEGfxVertexList* mesh, AEGfxTexture* texture) : Component (gameObject)
{
	sprite.mesh = mesh;
	sprite.texture = texture;
}

void StarBangBang::ImageComponent::SetTexture(AEGfxTexture* texture)
{
	sprite.texture = texture;
}

void StarBangBang::ImageComponent::SetMesh(AEGfxVertexList* mesh)
{
	sprite.mesh = mesh;
}

void StarBangBang::ImageComponent::Draw()
{
 	if (gameObject->active)
	{
		if (sprite.mesh && sprite.texture)
		{
			AEVec2 pos = gameObject->GetPos();
			Graphics::DrawImage(sprite.mesh, sprite.texture, pos, gameObject->transform.scale, gameObject->transform.rotation);

		}
	}
}
