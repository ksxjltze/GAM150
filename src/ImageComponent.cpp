#include "ImageComponent.h"
#include "Utils.h"

StarBangBang::ImageComponent::ImageComponent(GameObject* gameObject, AEGfxVertexList* mesh, AEGfxTexture* texture) : _Component (gameObject)
{
	this->mesh = mesh;
	this->texture = texture;
}

StarBangBang::_Component* StarBangBang::ImageComponent::Clone(GameObject* obj, _Component* component)
{
	ImageComponent* original = dynamic_cast<ImageComponent*>(component);
	return new ImageComponent(obj, original->mesh, original->texture);
}

void StarBangBang::ImageComponent::Draw()
{
 	if (gameObject->active)
	{
		AEVec2 pos = gameObject->GetPos();
		Graphics::DrawImage(mesh, texture, pos, gameObject->transform.scale, gameObject->transform.rotation);
	}
}
