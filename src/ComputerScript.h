
#pragma once
#include "ScriptComponent.h"
#include "Listener.h"

namespace StarBangBang
{
	class ComputerScript : public Script, public Listener
	{
	public:
		ComputerScript(GameObject* gameObject);

		void Start();
		void Update();
		void onNotify(Event e);

	private:
		bool enabled;
	};
}

