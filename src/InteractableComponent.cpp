#include "InteractableComponent.h"
#include <iostream>

StarBangBang::InteractableComponent::InteractableComponent(GameObject* gameObject) : Component(gameObject, id)
{
	enabled = false;
	type = INTERACTABLE_TYPE::TYPE_NONE;
}

StarBangBang::Component* StarBangBang::InteractableComponent::Clone(GameObject* gameObject, Component* component)
{
	return new InteractableComponent(gameObject);
}

void StarBangBang::InteractableComponent::OnUse()
{
	switch (type)
	{
	case INTERACTABLE_TYPE::TYPE_PRINTER:
		// event manager stuff here
		break;
	case INTERACTABLE_TYPE::TYPE_VENDING_MACHINE:
		// event manager stuff here
		break;
	}
}