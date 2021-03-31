#include "Distractor.h"
#include "Collider.h"
#include "DistractionEvent.h"
#include "CollisionEvent.h"
#include "constants.h"
#include "globals.h"

const static float DISTRACT_DURATION = 30.0f;

StarBangBang::Distractor::Distractor(GameObject* gameObject) : Script(gameObject), activated{ false }, duration{ DISTRACT_DURATION}, timer{duration}, roomNum(0)
{
	
}

void StarBangBang::Distractor::Start()
{

}

void StarBangBang::Distractor::Update()
{
	if (activated)
	{
		//SendDistractionEvent();
		timer -= g_dt;

		//Test active
		gameObject->transform.rotation += 90.0f * g_dt;

		if (timer <= 0)
		{
			activated = false;
			timer = duration;
		}
	}
}

void StarBangBang::Distractor::onNotify(Event e)
{
	if (e.id == EventId::COLLISION && !activated)
	{
		CollisionEvent data = std::any_cast<CollisionEvent>(e.context);
		if (data.first->gameObject->name == "Player" && data.second->gameObject == gameObject)
			SendDistractionEvent();
	}

}

void StarBangBang::Distractor::SendDistractionEvent()
{
	activated = true;
	DistractionEvent e{ gameObject };
	e.SendEvent();
}
