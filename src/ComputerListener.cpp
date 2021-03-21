#include "ComputerListener.h"
#include <iostream>

StarBangBang::ComputerListener::ComputerListener(GameObject* gameObject) : ListenerComponent(gameObject)
{

}

void StarBangBang::ComputerListener::onNotify(Event e)
{
	static int counter = 0;
	if (e.id == EventId::COMPUTER_CLICK)
	{
		std::cout << "dasd";
		++counter;
		if (counter > 5)
		{
			gameObject->active = false;
		}
	}
}
