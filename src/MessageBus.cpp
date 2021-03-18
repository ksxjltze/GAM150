#include "MessageBus.h"

void StarBangBang::MessageBus::RegisterListener(ListenerComponent* listener)
{
	listenerList.push_back(listener);
}

void StarBangBang::MessageBus::Update()
{
	//Event loop
	while (!eventQueue.empty())
	{
		for (auto listener : listenerList)
		{
			listener->onNotify(eventQueue.front());
			eventQueue.pop();
		}
	}
}

void StarBangBang::MessageBus::Notify(Event e)
{
	eventQueue.push(e);
}
