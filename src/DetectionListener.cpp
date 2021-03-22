#include "DetectionListener.h"
#include <iostream>

StarBangBang::DetectionListener::DetectionListener(GameObject* gameObject) : ListenerComponent(gameObject)
{

}

void StarBangBang::DetectionListener::onNotify(Event e)
{
	if (e.id == EventId::DETECTED)
	{

	}
}
