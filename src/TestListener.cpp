#include "TestListener.h"

/// <summary>
/// Override virtual function.
/// This function is called when listener receives a message from event system (Message Bus).
/// </summary>
void StarBangBang::TestListener::onNotify(Event e)
{
	//Check event type (id)
	//Do stuff if type match
	if (e.id == EventId::TEST)
	{
		//Cast context from std::any into std::string
		//std::any can be assigned to any type
		//Must be correctly casted into the type it was assigned to.
		//Similar to void ptr.
		std::string s = std::any_cast<const char*>(e.context);

		//Prints the string that was passed in as context for the event.
		std::cout << s << std::endl;
	}
}