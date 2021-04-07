#include "MessageBus.h"
#include "Listener.h"

void StarBangBang::MessageBus::Reset()
{
	listenerList.clear();

	while (!eventQueue.empty())
	{
		eventQueue.pop();
	}
}

void StarBangBang::MessageBus::RegisterListener(Listener* listener)
{
	listenerList.push_back(listener);
}

void StarBangBang::MessageBus::RegisterGlobalListener(Listener* listener)
{
	globalListenerList.push_back(listener);
}

bool StarBangBang::MessageBus::IsEventInQueue(EventId id)
{
	std::queue<Event> copyQueue;
	copyQueue = eventQueue;

	while (!eventQueue.empty())
	{
		if (copyQueue.front().id == id)
			return true;
	}
	return false;

}

void StarBangBang::MessageBus::Update()
{
	//Event loop
	while (!eventQueue.empty())
	{
		for (auto listener : listenerList)
		{
			if (listener->isOpen())
				listener->onNotify(eventQueue.front());
		}

		for (auto listener : globalListenerList)
		{
			if (listener->isOpen())
				listener->onNotify(eventQueue.front());
		}

		eventQueue.pop();
	}
}

void StarBangBang::MessageBus::Notify(Event e)
{
	eventQueue.push(e);
}
