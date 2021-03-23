#include "Distractor.h"
#include "Collider.h"

StarBangBang::Distractor::Distractor(GameObject* gameObject) : Script(gameObject)
{

}

void StarBangBang::Distractor::Start()
{

}

void StarBangBang::Distractor::Update()
{
	
}

void StarBangBang::Distractor::onNotify(Event e)
{
	if (e.id == EventId::COLLISION)
	{

	}
}

void StarBangBang::Distractor::SendDistractionEvent()
{

}
