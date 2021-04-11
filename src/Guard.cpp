/*!*********************************************************************
\title	  Captain Stealth
\file     Guard.cpp
\author   Liew Ruiheng Rayner (100%)
\par      DP email: r.liew\@digipen.edu
\date     10/04/2021

\brief
		  This file contains the function definitions of the Guard 
		  script class

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
***********************************************************************/

#include "Guard.h"
#include "Detector.h"
#include "Text.h"

using namespace StarBangBang;

/*!*********************************************************************
\brief
	Non-default constructor

\param gameObject
	The game object that will use this script
***********************************************************************/
Guard::Guard(GameObject* gameObject)
	: Script(gameObject)
	, state(GUARD_STATE::STATE_PATROL)
	, prevState(GUARD_STATE::STATE_NONE)
	, movement(nullptr)
	, vision(nullptr)
	, id(0)
	, roomNum(0)
{
}

/*!*********************************************************************
\brief
	Sets up the script
***********************************************************************/
void Guard::Start()
{
	movement = gameObject->GetComponent<GuardMovement>();
	vision = gameObject->GetComponent<GuardVision>();
}

/*!*********************************************************************
\brief
	Updates the script
***********************************************************************/
void Guard::Update()
{
	if (state != Guard::GUARD_STATE::STATE_CHASE)
	{
		AEVec2 targetPos;
		if (vision->GetDetector()->GetDetected(targetPos)) // Change to CHASE state if detected player
		{
			MessageBus::Notify({ EventId::PRINT_TEXT, std::string("DETECTED!") }); // Show "DETECTED" text on screen
			movement->SetTargetPos(targetPos);
			ChangeState(Guard::GUARD_STATE::STATE_CHASE);
		}
	}

	switch (state)
	{
	case Guard::GUARD_STATE::STATE_IDLE:
		movement->Idle();
		vision->Idle();
		break;
	case Guard::GUARD_STATE::STATE_PATROL:
		movement->Patrol();
		break;
	case Guard::GUARD_STATE::STATE_DISTRACTED:
		movement->Distracted();
		break;
	case Guard::GUARD_STATE::STATE_CHASE:
		movement->Chase();
		break;
	default:
		break;
	}
}

/*!*********************************************************************
\brief
	Changes the guard's state

\param _state
	The state the guard should change to
***********************************************************************/
void Guard::ChangeState(GUARD_STATE _state)
{
	prevState = state;

	// Exit previous state
	switch (prevState)
	{
	case Guard::GUARD_STATE::STATE_IDLE:
		break;
	case Guard::GUARD_STATE::STATE_PATROL:
		break;
	case Guard::GUARD_STATE::STATE_DISTRACTED:
		movement->OnExitDistracted();
		break;
	case Guard::GUARD_STATE::STATE_CHASE:
		break;
	default:
		break;
	}

	// Enter new state
	switch (_state)
	{
	case Guard::GUARD_STATE::STATE_IDLE:
		vision->OnEnterIdle();
		break;
	case Guard::GUARD_STATE::STATE_PATROL:
		vision->OnEnterPatrol();
		break;
	case Guard::GUARD_STATE::STATE_DISTRACTED:
		movement->OnEnterDistracted();
		vision->OnEnterDistracted();
		break;
	case Guard::GUARD_STATE::STATE_CHASE:
		movement->OnEnterChase();
		vision->OnEnterChase();
		break;
	default:
		break;
	}

	state = _state;
}