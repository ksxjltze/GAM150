#pragma once
#include "GameObject.h"
#include "constants.h"
#include "BusNode.h"

namespace StarBangBang
{
	class _Component : BusNode
	{
	public:
		_Component(GameObject* gameObject) { this->gameObject = gameObject; }
		inline virtual _Component* Clone(GameObject* obj, _Component*) const { return new _Component(obj); }
		virtual void Update() {};
		GameObject* gameObject { nullptr };
		virtual ~_Component() {}
	};
}