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
		static void RegisterListener(ListenerComponent* listener);
		static void Update();
		static void Notify(Event e);

	private:
		inline static std::queue<Event> eventQueue;
		inline static std::vector<ListenerComponent*>listenerList;
	};
}