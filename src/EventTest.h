#pragma once
#include "ScriptComponent.h"
#include "Subject.h"

namespace StarBangBang
{
	class EventTest : public Script
	{
	public:
		EventTest(GameObject* gameObject);
		void Start();
		void Update();
		Subject subject;
	};
}