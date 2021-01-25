#include "ObserverTest.h"
#include <iostream>

StarBangBang::ObserverTest::ObserverTest(GameObject* obj) : Script(obj)
{
}

void StarBangBang::ObserverTest::Start()
{

}

void StarBangBang::ObserverTest::Update()
{

}

void StarBangBang::ObserverTest::onNotify(const GameObject& obj, Event e)
{
	std::cout << "EVENT " << e.id << " test." << std::endl;
}
