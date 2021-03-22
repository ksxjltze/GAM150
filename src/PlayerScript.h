#pragma once
#include "ScriptComponent.h"
#include "Listener.h"

namespace StarBangBang
{
	class PlayerScript : public Script, public Listener
	{
	public:
		PlayerScript(GameObject* obj);
		void onNotify(Event e);
		bool isGameOver();
	private:
		bool gameover = false;

	};
}