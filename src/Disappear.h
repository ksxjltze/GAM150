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
		bool hidden, ventClosed;
		Sprite& ventOpen;
		Sprite& ventClose;
	};
}
