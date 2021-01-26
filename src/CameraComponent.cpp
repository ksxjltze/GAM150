#include "CameraComponent.h"

StarBangBang::CameraComponent::CameraComponent(GameObject* gameObject) : Component(gameObject)
{
	position = { 0, 0 };
}

StarBangBang::Component* StarBangBang::CameraComponent::Clone(GameObject* obj, Component*)
{
	return new CameraComponent(obj);
}

void StarBangBang::CameraComponent::Update()
{
	position = gameObject->transform.position;

	//temp
	AEGfxSetCamPosition(position.x, position.y);
}
