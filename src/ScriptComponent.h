#pragma once
#include "ComponentCRTP.h"
#include "Observer.h"

namespace StarBangBang
{
	class Script : public Component<Script>
	{
	public:
		inline Script(GameObject* gameObject) : Component(gameObject) {}
		inline void SetActive(bool status) { active = status; }

		virtual void Start() {};
		virtual void Update() {};

	private:
		friend class ScriptManager;
		bool active { true };
	};
}