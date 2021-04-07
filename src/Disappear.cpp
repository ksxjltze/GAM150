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
#include "SoundEvent.h"

const static float DISTRACT_DURATION = 30.0f;

StarBangBang::Disappear::Disappear(GameObject* gameObject, Sprite& ventOpen_, Sprite& ventClose_) 
	:Script(gameObject), ventOpen{ ventOpen_ }, ventClose{ ventClose_ }, hidden{ false }, ventClosed{ false }
{

}

void StarBangBang::Disappear::Start()
{
	gameObject->name = "Vent";
	ventClosed = false;
}

void StarBangBang::Disappear::Update()
{
	if (!hidden && ventClosed)
	{
		gameObject->GetComponent<ImageComponent>()->SetSprite(ventOpen);
		ventClosed = false;
	}

	if (hidden)
	{
		hidden = false;
	}

}

void StarBangBang::Disappear::onNotify(Event e)
{
	if (!hidden)
	{
		if (e.id == EventId::COLLISION)
		{
			CollisionEvent data = std::any_cast<CollisionEvent>(e.context);
			if (data.second->gameObject == gameObject)
			{
				if (data.first->gameObject->name == "Player" || data.first->gameObject->name == "Client")
				{
					if (!ventClosed)
					{
						SoundEvent eventVentOpen(SFX::VENT_CLOSE);
						eventVentOpen.SendEvent();
					}
					hidden = true;
					ventClosed = true;
					data.second->gameObject->GetComponent<ImageComponent>()->SetSprite(ventClose);
				}

			}
		}

	}
}

