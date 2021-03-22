#include "CollisionListener.h"
#include <iostream>
#include "MessageBus.h"

StarBangBang::CollisionListener::CollisionListener(GameObject* obj) : ListenerComponent(obj)
{
	MessageBus::RegisterListener(this);
}

void StarBangBang::CollisionListener::onNotify(Event e)
{
	if (e.id == EventId::COLLISION)
	{
		//std::cout << "COLLISION TRIGGER TEST\n" << std::endl;
	}
}
