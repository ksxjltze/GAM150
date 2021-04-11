#include "MessageBus.h"
#include "Listener.h"

/*!*************************************************************************
 * \brief
 * Resets the event system, clearing all listeners from the list and events fr
 ****************************************************************************/
void StarBangBang::MessageBus::Reset()
{
	listenerList.clear();

	while (!eventQueue.empty())
	{
		eventQueue.pop();
	}
}

/*!*************************************************************************
 * \brief
 * Registers a listener.
 * \param listener
 * Pointer to the listener object to register
***************************************************************************/
void StarBangBang::MessageBus::RegisterListener(Listener* listener)
{
	listenerList.push_back(listener);
}

/*!*************************************************************************
* \brief
 * Registers a listener that will persist throughout the whole program (e.g. AudioEngine).
 * \param listener Pointer to the listener to register.
 ***************************************************************************/
void StarBangBang::MessageBus::RegisterGlobalListener(Listener* listener)
{
	globalListenerList.push_back(listener);
}

/*!*************************************************************************
 * \brief
 * Checks if an event is in the queue.
 * \param id
 * Event id
 * \return
 * True if the event is the in queue, false otherwise.
***************************************************************************/
bool StarBangBang::MessageBus::IsEventInQueue(EventId id)
{
	std::queue<Event> copyQueue;
	copyQueue = eventQueue;

	while (!copyQueue.empty())
	{
		if (copyQueue.front().id == id)
			return true;
		copyQueue.pop();
	}
	return false;

}

/*!*************************************************************************
 * \brief
 * Update function that is called once a frame.
 * Dispatches all events from the event queue to each listener.
***************************************************************************/
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

/*!*************************************************************************
 * \brief
 * Adds an event to the event queue.
 *
 * \param e
 * Event to add
 ***************************************************************************/
void StarBangBang::MessageBus::Notify(Event e)
{
	eventQueue.push(e);
}
