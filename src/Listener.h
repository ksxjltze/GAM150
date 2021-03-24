#pragma once
#include "Event.h"
#include "MessageBus.h"

namespace StarBangBang
{
	class Listener
	{
	public:
		Listener() { MessageBus::RegisterListener(this); };
		virtual void onNotify(Event e) = 0;
	};
}