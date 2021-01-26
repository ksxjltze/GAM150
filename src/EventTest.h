#pragma once
#include "ScriptComponent.h"
#include "Subject.h"

namespace StarBangBang
{
	class EventTest : public Script
	{
	public:
		EventTest(GameObject* gameObject);
		inline Component* Clone(Component* component) {return new EventTest(component->gameObject);}
		void Start();
		void Update();
		Subject subject;
	private:
		int eventCount;
	};
}