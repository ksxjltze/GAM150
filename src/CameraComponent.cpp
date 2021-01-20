#include "CameraComponent.h"

StarBangBang::CameraComponent::CameraComponent(GameObject* gameObject) : Component(gameObject, id)
{
	position = { 0, 0 };
}

StarBangBang::Component* StarBangBang::CameraComponent::Clone(GameObject* gameObject, Component* component)
{
	return new CameraComponent(gameObject);
}

void StarBangBang::CameraComponent::Update()
{
	position = gameObject->transform.position;

	//temp
	AEGfxSetCamPosition(position.x, position.y);
}
