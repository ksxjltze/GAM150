#pragma once
#include "ScriptComponent.h"
#include "Subject.h"

namespace StarBangBang
{
	class EventTest : public Script
	{
	public:
		EventTest(GameObject* gameObject);
		inline Component* Clone(GameObject* obj, Component* component = nullptr)
		{
			if (component->id != id)
				return nullptr;

			return new EventTest(obj);
		};
		void Start();
		void Update();
		Subject subject;
	private:
		int eventCount;
	};
}