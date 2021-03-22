#include "ComputerListener.h"
#include <iostream>
#include "Collider.h"
#include "constants.h"
#include "MessageBus.h"
#include <sstream>

StarBangBang::ComputerListener::ComputerListener(GameObject* gameObject) : ListenerComponent(gameObject), counter{ 0 }
{
	MessageBus::RegisterListener(this);
}

void StarBangBang::ComputerListener::onNotify(Event e)
{
	if (e.id == EventId::COMPUTER_CLICK)
	{
		++counter;
		std::cout << "Hax: " << counter;
		if (counter >= CONSTANTS::COMPUTER_COUNT)
		{
			BoxCollider* col = gameObject->GetComponent<BoxCollider>();
			if (col)
			{
				std::string str;
				std::ostringstream is(str);
				is << "Computers Left: " << CONSTANTS::COMPUTER_COUNT - counter;

				MessageBus::Notify({EventId::PRINT_TEXT, str});
				gameObject->active = false;
				col->isTrigger = true;
			}
		}
	}
}
