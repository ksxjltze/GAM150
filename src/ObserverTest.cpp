#include "ObserverTest.h"
#include <iostream>

StarBangBang::ObserverTest::ObserverTest(GameObject* obj) : Script(obj)
{
	eventCount = 0;
}

void StarBangBang::ObserverTest::Start()
{

}

void StarBangBang::ObserverTest::Update()
{

}

void StarBangBang::ObserverTest::onNotify(const GameObject& obj, Event e)
{
	std::cout << "SUBJECT CALL COUNT: " << e.id << " " << std::endl;
	std::cout << "OBSERVER NOTIFY COUNT: " << ++eventCount << " " << std::endl;
}
