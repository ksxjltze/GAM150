#include "Disappear.h"
#include "Collider.h"
#include "CollisionEvent.h"
#include "constants.h"
#include "globals.h"
#include "ImageComponent.h"
#include "ObjectManager.h"

const static float DISTRACT_DURATION = 30.0f;

StarBangBang::Disappear::Disappear(GameObject* gameObject) : Script(gameObject), disappeared{ false }
{

}

void StarBangBang::Disappear::Start()
{

}

void StarBangBang::Disappear::Update()
{
	if(disappeared)
	{	
		disappeared = false;
	}
	else if (!disappeared)
	{
		objMgr->Find("Player")->GetComponent<ImageComponent>()->active = true;
		objMgr->Find("Client")->GetComponent<ImageComponent>()->active = true;
	}

}

void StarBangBang::Disappear::onNotify(Event e)
{
	if (e.id == EventId::COLLISION && !disappeared)
	{
		CollisionEvent data = std::any_cast<CollisionEvent>(e.context);
		if (data.second->gameObject == gameObject)
		{
			if (data.first->gameObject->name == "Player")
			{
				data.first->gameObject->GetComponent<ImageComponent>()->active = false;
				disappeared = true;
			}
			else if (data.first->gameObject->name == "Client")
			{
				data.second->gameObject->GetComponent<ImageComponent>()->active = false;
				disappeared = true;
			}

		}
	}
}

