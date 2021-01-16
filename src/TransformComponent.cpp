#include "TransformComponent.h"

TempTeam::TransformComponent::TransformComponent(GameObject* gameObject)
{
	this->gameObject = gameObject;
	position.x = 0;
	position.y = 0;
}
