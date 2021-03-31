#include "TestInteractable.h"
#include "MessageBus.h"

/// <summary>
/// Sends a message to the event system
/// </summary>
void StarBangBang::TestInteractable::Interact()
{
	//Event to send
	Event e;
	e.id = EventId::TEST;
	e.context = "TESTING TEST INTERACTABLE EVENT 1";

	//Second event
	Event e2 = { EventId::TEST, "TESTING TEST INTERACTABLE EVENT 2" };

	//Notify event system
	//Adds an event to the queue and sends it to all listeners
	MessageBus::Notify(e);
	MessageBus::Notify(e2);
}