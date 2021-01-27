#pragma once
#include "ScriptComponent.h"
#include "Observer.h"

namespace StarBangBang
{
	class ObserverTest : public Script, public Observer
	{
	public:
		ObserverTest(GameObject* obj);
		inline _Component* Clone(GameObject* obj, _Component*) { return new ObserverTest(obj); };
		void Start();
		void Update();
		void onNotify(const GameObject& obj, Event e);
	private:
		int eventCount;
	};
}