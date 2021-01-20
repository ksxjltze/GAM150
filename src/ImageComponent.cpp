#include "ImageComponent.h"
#include "Utils.h"

StarBangBang::ImageComponent::ImageComponent(GameObject* gameObject, AEGfxVertexList* mesh, AEGfxTexture* texture) : Component (gameObject, id)
{
	this->mesh = mesh;
	this->texture = texture;
}

void StarBangBang::ImageComponent::Draw()
{
	if (gameObject->active)
	{
		AEVec2 pos = gameObject->GetPos();
		DrawImage(mesh, texture, pos);
	}
}
