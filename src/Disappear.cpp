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
	:Script(gameObject), ventOpen{ ventOpen_ }, ventClose{ ventClose_ }, disappeared{false}
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
		gameObject->GetComponent<ImageComponent>()->SetSprite(ventOpen);
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
				data.second->gameObject->GetComponent<ImageComponent>()->SetSprite(ventClose);
				disappeared = true;
			}
			else if (data.first->gameObject->name == "Client")
			{
				data.first->gameObject->GetComponent<ImageComponent>()->active = false;
				data.second->gameObject->GetComponent<ImageComponent>()->SetSprite(ventClose);
				disappeared = true;
			}

		}
	}
}

