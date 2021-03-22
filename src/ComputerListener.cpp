#include "ComputerListener.h"
#include <iostream>
#include "Collider.h"
#include "constants.h"

StarBangBang::ComputerListener::ComputerListener(GameObject* gameObject) : ListenerComponent(gameObject), counter{ 0 }
{

}

void StarBangBang::ComputerListener::onNotify(Event e)
{
	if (e.id == EventId::COMPUTER_CLICK)
	{
		std::cout << "dasd";
		++counter;
		if (counter >= CONSTANTS::COMPUTER_COUNT)
		{
			BoxCollider* col = gameObject->GetComponent<BoxCollider>();
			if (col)
			{
				gameObject->active = false;
				col->isTrigger = true;
			}
		}
	}
}
