
#pragma once
#include "ScriptComponent.h"

namespace StarBangBang
{
	class ComputerScript : public Script
	{
	public:
		enum class COMPUTER_STATE
		{
			STATE_IDLE = 0,
		};

		ComputerScript(GameObject* gameObject);

		void Start();
		void Update();

	private:

	};
}

