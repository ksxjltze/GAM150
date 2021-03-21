#pragma once
#include <vector>
#include <queue>
#include "Event.h"
#include "ListenerComponent.h"

namespace StarBangBang
{
	class MessageBus
	{
	public:
		static void Reset();
		static void RegisterListener(Listener* listener);
		static void RegisterGlobalListener(Listener* listener);
		static void Update();
		static void Notify(Event e);

	private:
		inline static std::queue<Event> eventQueue;
		inline static std::vector<Listener*>listenerList;
		inline static std::vector<Listener*>globalListenerList;
	};
}