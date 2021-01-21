#include "CameraComponent.h"

StarBangBang::CameraComponent::CameraComponent(GameObject* gameObject) : Component(gameObject, id)
{
	position = { 0, 0 };
}

StarBangBang::Component* StarBangBang::CameraComponent::Clone(GameObject* obj, Component* component = nullptr)
{
	if (component->id != id)
		return nullptr;

	return new CameraComponent(obj);
}

void StarBangBang::CameraComponent::Update()
{
	position = gameObject->transform.position;

	//temp
	AEGfxSetCamPosition(position.x, position.y);
}
