#include "Disappear.h"
#include "Collider.h"
#include "CollisionEvent.h"
#include "constants.h"
#include "globals.h"
#include "ImageComponent.h"
#include "ObjectManager.h"
#include "GraphicsManager.h"
#include "Level_Demo.h"

const static float DISTRACT_DURATION = 30.0f;

StarBangBang::Disappear::Disappear(GameObject* gameObject) : Script(gameObject)
{

}

void StarBangBang::Disappear::Start()
{

}

void StarBangBang::Disappear::Update()
{
	if (playerHidden)
	{
		playerHidden = false;
	}
	else
	{
		GameObject* player = objMgr->Find("Player");
		if (!player->visible)
			player->visible = true;
	}

	if (clientHidden)
	{
		clientHidden = false;
	}
	else
	{
		GameObject* client = objMgr->Find("Client");
		if (!client->visible)
			client->visible = true;
	}

}

void StarBangBang::Disappear::onNotify(Event e)
{
	if (e.id == EventId::COLLISION)
	{
		CollisionEvent data = std::any_cast<CollisionEvent>(e.context);
		if (data.second->gameObject == gameObject)
		{
			if (data.first->gameObject->name == "Player")
			{
				data.first->gameObject->visible = false;
				//data.first->gameObject->GetComponent<ImageComponent>()->active = false;
				playerHidden = true;
			}
			if (data.first->gameObject->name == "Client")
			{
				data.first->gameObject->visible = false;
				//data.first->gameObject->GetComponent<ImageComponent>()->active = false;
				clientHidden = true;
			}

		}
	}
}

