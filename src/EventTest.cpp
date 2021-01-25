#include "EventTest.h"

StarBangBang::EventTest::EventTest(GameObject* gameObject) : Script(gameObject)
{

}

void StarBangBang::EventTest::Start()
{
	subject.notify(*gameObject, { 69 });
}

void StarBangBang::EventTest::Update()
{

}
