/*!*********************************************************************
\title	  Captain Stealth
\file     Disappear.cpp
\author   Sim Chin Hin
\par      DP email: s.chinhin\@digipen.edu
\date     11/04/2021

\brief
		  This file contains the script class players
		  disappearing into the vents

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
***********************************************************************/

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

/*!*********************************************************************
\brief
	Non-default constructor

\param gameObject
	The game object that will use this script
\param ventOpen_
	open vent sprite
\param ventClose_
	closed vent sprite
***********************************************************************/
StarBangBang::Disappear::Disappear(GameObject* gameObject, Sprite& ventOpen_, Sprite& ventClose_) 
	:Script(gameObject), ventOpen{ ventOpen_ }, ventClose{ ventClose_ }, hidden{ false }, ventClosed{ false }
{

}
/*!*********************************************************************
\brief
	Initialise vent's starting state
***********************************************************************/
void StarBangBang::Disappear::Start()
{
	gameObject->name = "Vent";
	ventClosed = false;
}
/*!*********************************************************************
\brief
	Update vent's current state
***********************************************************************/
void StarBangBang::Disappear::Update()
{
	if (!hidden && ventClosed)
	{
		gameObject->GetComponent<ImageComponent>()->SetSprite(ventOpen);
		SoundEvent eventVentOpen(SFX::VENT_OPEN);
		eventVentOpen.SendEvent();
		ventClosed = false;
	}

	if (hidden)
	{
		hidden = false;
	}

}
/*!*********************************************************************
\brief
	Change vent's sprite and state when notified
***********************************************************************/
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
						SoundEvent eventVentClose(SFX::VENT_CLOSE);
						eventVentClose.SendEvent();
					}
					hidden = true;
					ventClosed = true;
					data.second->gameObject->GetComponent<ImageComponent>()->SetSprite(ventClose);
				}

			}
		}

	}
}

