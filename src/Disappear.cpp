#include "Disappear.h"
#include "Collider.h"
#include "CollisionEvent.h"
#include "constants.h"
#include "globals.h"
#include "ImageComponent.h"
#include "ObjectManager.h"
#include "GraphicsManager.h"
#include "Level_Demo.h"
#include "Sprite.h"

const static float DISTRACT_DURATION = 30.0f;

StarBangBang::Disappear::Disappear(GameObject* gameObject, Sprite& ventOpen_, Sprite& ventClose_) 
	:Script(gameObject), ventOpen{ ventOpen_ }, ventClose{ ventClose_ }
{

}

void StarBangBang::Disappear::Start()
{

}

void StarBangBang::Disappear::Update()
{
	if (clientHidden == false && playerHidden == false)
	{
		gameObject->GetComponent<ImageComponent>()->SetSprite(ventOpen);
	}

	if (playerHidden)
	{
		playerHidden = false;
	}
	else
	{
		GameObject* player = objMgr->Find("Player");
		if (!player->visible)
		{
			player->visible = true;
			player->GetComponent<BoxCollider>()->isTrigger = false;
		}
	}

	if (clientHidden)
	{
		clientHidden = false;
	}
	else
	{
		GameObject* client = objMgr->Find("Client");
		if (!client->visible)
		{
			client->visible = true;
			client->GetComponent<BoxCollider>()->isTrigger = false;
		}
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
				data.first->gameObject->GetComponent<BoxCollider>()->isTrigger = true;
				data.second->gameObject->GetComponent<ImageComponent>()->SetSprite(ventClose);
				playerHidden = true;
			}
			if (data.first->gameObject->name == "Client")
			{
				data.first->gameObject->visible = false;
				data.first->gameObject->GetComponent<BoxCollider>()->isTrigger = true;
				data.second->gameObject->GetComponent<ImageComponent>()->SetSprite(ventClose);
				clientHidden = true;
			}

		}
	}
}

