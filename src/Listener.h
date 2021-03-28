#pragma once
#include "Event.h"
#include "MessageBus.h"

namespace StarBangBang
{
	class Listener
	{
	public:
		Listener() : open{ true } { MessageBus::RegisterListener(this); };
		virtual void onNotify(Event e) = 0;
		inline bool isOpen() { return open; };
	protected:
		bool open;
	};
}