#pragma once
#include "Component.h"

namespace StarBangBang
{
	class Script : public Component
	{
	public:
		const static int id = Constants::ComponentType::SCRIPT;
		inline Script(GameObject* gameObject) : Component(gameObject, id)
		{
			this->gameObject = gameObject;
		}
		virtual void Start() = 0;
		virtual void Update() = 0;
	};
}