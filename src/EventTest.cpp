#include "EventTest.h"

StarBangBang::EventTest::EventTest(GameObject* gameObject) : Script(gameObject)
{
	eventCount = 0;
}

void StarBangBang::EventTest::Start()
{
	subject.notify(*gameObject, { ++eventCount });
}

void StarBangBang::EventTest::Update()
{

}
