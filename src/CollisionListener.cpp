#include "CollisionListener.h"
#include <iostream>
#include "MessageBus.h"

StarBangBang::CollisionListener::CollisionListener(GameObject* obj) : ListenerComponent(obj)
{
	
}

void StarBangBang::CollisionListener::onNotify(Event e)
{
	if (e.id == EventId::COLLISION)
	{
		
	}
}
