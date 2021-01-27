#include "InteractableComponent.h"
#include <iostream>

StarBangBang::InteractableComponent::InteractableComponent(GameObject* obj) : _Component(obj)
{
	enabled = false;
	type = INTERACTABLE_TYPE::TYPE_NONE;
}

StarBangBang::_Component* StarBangBang::InteractableComponent::Clone(GameObject* obj, _Component*)
{
	return new InteractableComponent(obj);
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