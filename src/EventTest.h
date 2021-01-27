#pragma once
#include "ScriptComponent.h"
#include "Subject.h"

namespace StarBangBang
{
	class EventTest : public Script
	{
	public:
		EventTest(GameObject* gameObject);
		inline _Component* Clone(GameObject* obj, _Component*) {return new EventTest(obj);}
		void Start();
		void Update();
		Subject subject;
	private:
		int eventCount;
	};
}