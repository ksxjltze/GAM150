#pragma once
#include "Component.h"

namespace StarBangBang
{
	class Script : public Component
	{
	public:
		inline Script(GameObject* gameObject) : Component(gameObject, id)
		{
			this->gameObject = gameObject;
		}
		virtual void Start() = 0;
		virtual void Update() = 0;
		const static int id = 1;
	};
}