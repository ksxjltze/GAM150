#include "ImageComponent.h"
#include "Utils.h"

StarBangBang::ImageComponent::ImageComponent(GameObject* gameObject, AEGfxVertexList* mesh, AEGfxTexture* texture) : Component (gameObject, id)
{
	this->mesh = mesh;
	this->texture = texture;
}

StarBangBang::Component* StarBangBang::ImageComponent::Clone(GameObject* gameObject, Component* component)
{
	ImageComponent* original = dynamic_cast<ImageComponent*>(component);
	return new ImageComponent(gameObject, original->mesh, original->texture);
}

void StarBangBang::ImageComponent::Draw()
{
	if (gameObject->active)
	{
		AEVec2 pos = gameObject->GetPos();
		DrawImage(mesh, texture, pos);
	}
}
