#pragma once
#include "GameObject.h"

namespace StarBangBang
{
	class Component
	{
	public:
		inline GameObject* GetGameObject() { return gameObject; }
		inline virtual Component* Copy(const Component& original)
		{
			id = original.id;
			return this;
		}
		virtual void Update() {};
		int id { 0 };
		GameObject* gameObject { nullptr };
	};
}