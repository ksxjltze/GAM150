
#pragma once
#include "ScriptComponent.h"
#include "Listener.h"

namespace StarBangBang
{
	class ComputerScript : public Script, public Listener
	{
	public:
		enum class COMPUTER_STATE
		{
			STATE_IDLE = 0,
		};

		ComputerScript(GameObject* gameObject);

		void Start();
		void Update();
		void onNotify(Event e);

	private:
		bool enabled;
	};
}

