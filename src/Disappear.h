#pragma once
#include "ScriptComponent.h"
#include "Listener.h"
#include "Sprite.h"

namespace StarBangBang
{
	class Disappear : public Script, public Listener
	{
	public:
		Disappear(GameObject* gameObject, Sprite& ventOpen_, Sprite& ventClose_);
		void Start();
		void Update();
		void onNotify(Event e);

	private:
		bool playerHidden = false;
		bool clientHidden = false;
		Sprite& ventOpen;
		Sprite& ventClose;
	};
}
