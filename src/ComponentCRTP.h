#pragma once
#include "Component.h"

namespace StarBangBang
{
	template <typename ComponentType>
	class Component : public _Component
	{
	public:
		Component(GameObject* obj) : _Component(obj) {}
		_Component* Clone(GameObject* obj, _Component*) const override //const to prevent original component from being modified
		{
			_Component* clonedComponent = new ComponentType(static_cast<ComponentType const&>(*this));
			clonedComponent->gameObject = obj;
			return clonedComponent;
		}
	};
}
