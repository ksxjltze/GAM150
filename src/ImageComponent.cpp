#include "ImageComponent.h"
#include "Utils.h"

StarBangBang::ImageComponent::ImageComponent(GameObject* gameObject, AEGfxVertexList* mesh, AEGfxTexture* texture)
{
	this->mesh = mesh;
	this->texture = texture;
	this->gameObject = gameObject;
	Component::id = id;
}

void StarBangBang::ImageComponent::Draw()
{
	if (gameObject->active)
	{
		AEVec2 pos = gameObject->GetPos();
		DrawImage(mesh, texture, pos);
	}
}
