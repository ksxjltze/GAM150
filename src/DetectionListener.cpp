#include "DetectionListener.h"
#include <iostream>

StarBangBang::DetectionListener::DetectionListener(GameObject* gameObject) : ListenerComponent(gameObject)
{

}

void StarBangBang::DetectionListener::onNotify(Event e)
{
	if (e.id == EventId::DETECTED)
	{
		try
		{
			std::string s = std::any_cast<std::string>(e.context);
			std::cout << s << std::endl;
		}
		catch (const std::exception&)
		{
			std::cout << "ERROR" << std::endl;
			return;
		}

	}
}
