#pragma once
#include "ScriptComponent.h"
#include "Listener.h"

namespace StarBangBang
{
	class PlayerScript : public Script, public Listener
	{
	public:
		PlayerScript(GameObject* obj);
		void Update();
		void onNotify(Event e);
		bool isGameOver();
		bool isWin();
		void Start();
	private:
		bool gameover = false;
		bool playerEscaped = false;
		bool clientEscaped = false;

	};
}