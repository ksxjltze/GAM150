#pragma once
#include "Component.h"
#include "Observer.h"

namespace StarBangBang
{
	class Script : public Component
	{
	public:
		inline Script(GameObject* gameObject) : Component(gameObject) {this->gameObject = gameObject;}
		virtual Component* Clone(GameObject* gameObject, Component* component) = 0;
		inline void SetActive(bool status) { active = status; }

		virtual void Start() {};
		virtual void Update() {};

	private:
		friend class ScriptManager;
		bool active { true };
	};
}