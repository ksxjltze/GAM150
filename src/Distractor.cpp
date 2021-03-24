#include "Distractor.h"
#include "Collider.h"
#include "DistractionEvent.h"
#include "CollisionEvent.h"

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
		CollisionEvent data = std::any_cast<CollisionEvent>(e.context);
		if (data.first->gameObject->name == "Player")
			SendDistractionEvent();
	}

	//Test
	if (e.id == EventId::DISTRACTION)
	{
		//printf("DISTRACT\n");
	}
}

void StarBangBang::Distractor::SendDistractionEvent()
{
	DistractionEvent e;
	e.SendEvent();
}
