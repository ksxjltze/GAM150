/*!*********************************************************************
\title	  Captain Stealth
\file     Distractor.cpp
\author   Sim Chin Hin
\par      DP email: s.chinhin\@digipen.edu
\date     11/04/2021

\brief
		  This file contains the Distractor script class

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
***********************************************************************/
#include "Distractor.h"
#include "Collider.h"
#include "DistractionEvent.h"
#include "CollisionEvent.h"
#include "constants.h"
#include "globals.h"

const static float DISTRACT_DURATION = 20.0f;
/*!*********************************************************************
\brief
	Distractor constructor
\param	gameObject
	gameObject that will be used
***********************************************************************/
StarBangBang::Distractor::Distractor(GameObject* gameObject) : Script(gameObject), activated{ false }, duration{ DISTRACT_DURATION}, timer{duration}, scaleTimer(0.f), roomNum(0)
{
}
/*!*********************************************************************
\brief
	Start state of the distractor
***********************************************************************/
void StarBangBang::Distractor::Start()
{
}
/*!*********************************************************************
\brief
	Update distractor's current state
***********************************************************************/
void StarBangBang::Distractor::Update()
{
	if (activated)
	{
		//SendDistractionEvent();
		timer -= g_dt;

		
		gameObject->transform.scale.x += sin(timer * PI) * g_dt;
		gameObject->transform.scale.y += cos(timer * PI) * g_dt;


		gameObject->transform.scale.x =	 AEClamp(gameObject->transform.scale.x, 0.6f, 1.0f);
		gameObject->transform.scale.y  = AEClamp(gameObject->transform.scale.y, 0.7f, 3.5f);
		
		//scaleTimer += g_dt;
		//scaleTimerY += g_dt;

		////Test active
		//gameObject->transform.scale.x += cos(scaleTimer * PI) * 0.02f;
		//gameObject->transform.scale.y += sin(scaleTimerY * PI) * 0.02f;

		//if (gameObject->transform.scale.x <= 0.8f)
		//	scaleTimer = 0.f;
		//else if (gameObject->transform.scale.x >= 1.2f)
		//		scaleTimer = 15.f;

		//if (gameObject->transform.scale.y <= 0.8f)
		//	scaleTimerY = 15.f;
		//else if (gameObject->transform.scale.y >= 1.8f)
		//	scaleTimerY = 0.f;

		if (timer <= 0)
		{
			activated = false;
			timer = duration;
			gameObject->transform.scale = { 1.f, 1.f };
		}
	}
}
/*!*********************************************************************
\brief
	Update distractor's time and animation when activated
***********************************************************************/
void StarBangBang::Distractor::onNotify(Event e)
{
	if (e.id == EventId::COLLISION && !activated)
	{
		CollisionEvent data = std::any_cast<CollisionEvent>(e.context);
		if ((data.first->gameObject->name == "Player" || data.first->gameObject->name == "Client") && data.second->gameObject == gameObject)
			SendDistractionEvent();
	}

}
/*!*********************************************************************
\brief
	Sends distraction event to guards
***********************************************************************/
void StarBangBang::Distractor::SendDistractionEvent()
{
	activated = true;
	DistractionEvent e{ gameObject };
	e.SendEvent();
}
