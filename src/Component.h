#pragma once
#include "GameObject.h"
#include "constants.h"

namespace StarBangBang
{
	class _Component
	{
	public:
		_Component(GameObject* gameObject) { this->gameObject = gameObject; }
		inline virtual _Component* Clone(GameObject* obj, _Component*) const { return new _Component(obj); }
		virtual void Start() {};
		virtual void Update() {};
		GameObject* gameObject { nullptr };
		virtual ~_Component() {}
		bool active { true };
		Component();
	};
}