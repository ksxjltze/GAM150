#pragma once
#include "ScriptComponent.h"
#include "Listener.h"

namespace StarBangBang
{
	class Door;
	class Key : public Script, public Listener
	{
	public:
		Key(GameObject* obj, Door* door);

		bool isCollected();
		void Pickup();
		void onNotify(Event e);

		void Start();
		void Update();
	private:
		bool flip{ false };
		float scale;
		bool collected;
		Door* door;
	};
}