#pragma once
#include "Component.h"

namespace StarBangBang
{
	template <typename ComponentType>
	class Component : public GameComponent
	{
	public:
		Component(GameObject* obj) : GameComponent(obj) {}
		GameComponent* Clone(GameObject* obj, GameComponent*) const override //const to prevent original component from being modified
		{
			GameComponent* clonedComponent = new ComponentType(static_cast<ComponentType const&>(*this));
			clonedComponent->gameObject = obj;
			return clonedComponent;
		}
	};
}
