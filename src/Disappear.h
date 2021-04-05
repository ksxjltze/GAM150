#pragma once
#include "ScriptComponent.h"
#include "Listener.h"

namespace StarBangBang
{
	class Disappear : public Script, public Listener
	{
	public:
		Disappear(GameObject* gameObject);

		void Start();
		void Update();
		void onNotify(Event e);

	private:
		bool playerHidden{ false };
		bool clientHidden{ false };
	};
}
