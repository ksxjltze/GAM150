#pragma once
#include "Component.h"

namespace StarBangBang
{
	template <typename ComponentType>
	class ComponentCRTP : public Component
	{
	public:
		ComponentCRTP(GameObject* obj) : Component(obj) {}
		Component* Clone(GameObject* obj) const //const to prevent original component from being modified
		{
			Component* clonedComponent = new ComponentType(static_cast<ComponentType const&>(*this));
			clonedComponent->gameObject = obj;
			return clonedComponent;
		}
	};
}
