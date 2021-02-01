#pragma once
#include "ScriptComponent.h"
#include "Observer.h"

namespace StarBangBang
{
	class ObserverTest : public Script, public Observer
	{
	public:
		ObserverTest(GameObject* obj);
		void Start();
		void Update();
		void onNotify(const GameObject& obj, Event e);
	private:
		int eventCount;
	};
}