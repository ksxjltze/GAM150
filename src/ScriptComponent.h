#pragma once
#include "Component.h"
#include "Observer.h"

namespace StarBangBang
{
	class Script : public _Component
	{
	public:
		inline Script(GameObject* gameObject) : _Component(gameObject) {this->gameObject = gameObject;}
		virtual _Component* Clone(GameObject* gameObject, _Component* component) = 0;
		inline void SetActive(bool status) { active = status; }

		virtual void Start() {};
		virtual void Update() {};

	private:
		friend class ScriptManager;
		bool active { true };
	};
}