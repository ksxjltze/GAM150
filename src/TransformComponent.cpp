#include "TransformComponent.h"

StarBangBang::TransformComponent::TransformComponent(GameObject* gameObject)
{
	this->gameObject = gameObject;
	position.x = 0;
	position.y = 0;
}
