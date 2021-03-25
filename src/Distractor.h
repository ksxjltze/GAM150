#pragma once
#include "ScriptComponent.h"
#include "Listener.h"

namespace StarBangBang
{
	class Distractor : public Script, public Listener
	{
	public:
		Distractor(GameObject* gameObject);

		void Start();
		void Update();
		void onNotify(Event e);
		void SendDistractionEvent();
	private:
		bool activated;
		float duration;
		float timer;
	};
}
