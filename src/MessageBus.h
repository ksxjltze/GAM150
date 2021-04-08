#pragma once
#include <vector>
#include <queue>
#include "Event.h"

namespace StarBangBang
{
	class Listener;

	class MessageBus
	{
	public:
		static void Reset();
		static void RegisterGlobalListener(Listener* listener);
		static bool IsEventInQueue(EventId id);
		static void Update();
		static void Notify(Event e);
		friend class Listener;

	private:
		static void RegisterListener(Listener* listener);
		inline static std::queue<Event> eventQueue;
		inline static std::vector<Listener*>listenerList;
		inline static std::vector<Listener*>globalListenerList;
	};
}