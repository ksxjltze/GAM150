#include "Subject.h"

void StarBangBang::Subject::notify(const GameObject& obj, Event event)
{
	for (Observer* observer : observerList)
	{
		observer->onNotify(obj, event);
	}
}

void StarBangBang::Subject::addObserver(Observer* observer)
{
	observerList.push_back(observer);
}

void StarBangBang::Subject::removeObserver(Observer* observer)
{
	//WIP
	for (int i = 0; i < observerList.size(); i++)
	{
		if (observer == observerList[i])
		{
			observerList.erase(observerList.begin() + i);
		}
	}
}
