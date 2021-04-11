/*!*********************************************************************
\title	  Captain Stealth
\file     GuardVision.cpp
\author   Liew Ruiheng Rayner (100%)
\par      DP email: r.liew\@digipen.edu
\date     10/04/2021

\brief
		  This file contains the function definitions of the
		  GuardVision script class

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
***********************************************************************/

#include "GuardVision.h"
#include "Guard.h"
#include"GuardMovement.h"
#include "Detector.h"
#include "globals.h"

using namespace StarBangBang;

/*!*********************************************************************
\brief
	Non-default constructor

\param gameObject
	The game object that will use this script
***********************************************************************/
GuardVision::GuardVision(GameObject* gameObject)
	: Script(gameObject)
	, movement(nullptr)
	, detector(nullptr)
	, rotation(0.f)
	, rotSpeed(90.f)
	, idleDuration(1.5f)
	, prevRot(-1)
	, currRot(0)
	, turn(false)
{
}

/*!*********************************************************************
\brief
	Sets up the script
***********************************************************************/
void GuardVision::Start()
{
	movement = gameObject->GetComponent<GuardMovement>();
	detector = gameObject->GetComponent<Detector>();
}

/*!*********************************************************************
\brief
	Updates the script. Rotates guard's vision to look in the direction
	of the next position it is going to.
***********************************************************************/
void GuardVision::Update()
{
	AEVec2 defaultForward = { 0, 1 };

	if (movement->IsMoving())
	{
		AEVec2 targetDir, targetPos, goPos;
		AEVec2 defaultLeft = { -1, 0 };
		targetPos = movement->GetNextPos();
		goPos = gameObject->GetPos();

		AEVec2Sub(&targetDir, &targetPos, &goPos);
		AEVec2Normalize(&targetDir, &targetDir);

		float dpResult = AEVec2DotProduct(&defaultForward, &targetDir);
		float targetRot = AERadToDeg(AEACos(dpResult));

		float dp = AEVec2DotProduct(&defaultLeft, &targetDir);
		if (dp < 0.f)
			targetRot = -targetRot;

		currRot = static_cast<int>(rint(targetRot));

		// check if guard has changed direction
		if (currRot != prevRot)
		{
			if (targetRot > 0 && rotation < 0.f)
			{
				if ((static_cast<int>(rotation) + static_cast<int>(targetRot)) != 0)
					targetRot = -targetRot;
			}
			else if (targetRot < 0 && rotation > 0.f)
			{
				if ((static_cast<int>(rotation) + static_cast<int>(targetRot)) != 0)
					targetRot = -targetRot;
			}

			prevRot = currRot;
			turn = true;
			movement->SetTurning(true);
		}

		// only update rotation when guard is changing direction
		if (turn)
		{
			if (gameObject->GetComponent<Guard>()->GetState() == Guard::GUARD_STATE::STATE_PATROL
				&& !movement->GetGoingToPatrolPoint())
			{
				idleDuration -= g_dt;
				if (idleDuration > 0.f)
					return;
			}

			if (rotation + 3.f < targetRot)
			{
				rotation += rotSpeed * g_dt;
				FaceTowardsRotation();
			}
			else if (rotation - 3.f > targetRot)
			{
				rotation -= rotSpeed * g_dt;
				FaceTowardsRotation();
			}
			
			if ((rotation - targetRot) >= -3.f && (rotation - targetRot) <= 3.f)
			{
				movement->SetTurning(false);
				turn = false;
				rotation = targetRot;
				idleDuration = 1.5f;
				detector->SetFacingDir(targetDir);
			}
			
			detector->Rotate(rotation);
		}
	}
}

/*!*********************************************************************
\brief
	Set variables upon entering idle state
***********************************************************************/
void GuardVision::OnEnterIdle()
{
	rotSpeed = 90.f;
}

/*!*********************************************************************
\brief
	Guard's idle vision behaviour
***********************************************************************/
void GuardVision::Idle()
{
	if (gameObject->GetComponent<Guard>()->GetPrevState() == Guard::GUARD_STATE::STATE_DISTRACTED)
	{
		AEVec2 defaultForward = { 0, 1 };
		AEVec2 targetDir, targetPos, goPos;
		AEVec2 defaultLeft = { -1, 0 };
		targetPos = movement->GetTargetPos(); // look at distraction object
		goPos = gameObject->GetPos();

		AEVec2Sub(&targetDir, &targetPos, &goPos);
		AEVec2Normalize(&targetDir, &targetDir);

		float dpResult = AEVec2DotProduct(&defaultForward, &targetDir);
		float targetRot = AERadToDeg(AEACos(dpResult));

		float dp = AEVec2DotProduct(&defaultLeft, &targetDir);
		if (dp < 0.f)
			targetRot = -targetRot;

		detector->SpanVision(targetRot - 90.f, targetRot + 90.f, 50.f);
	}
}

/*!*********************************************************************
\brief
	Set variables upon entering patrol state
***********************************************************************/
void GuardVision::OnEnterPatrol()
{
	rotSpeed = 90.f;
}

/*!*********************************************************************
\brief
	Set variables upon entering distracted state
***********************************************************************/
void GuardVision::OnEnterDistracted()
{
	rotSpeed = 350.f;
}

/*!*********************************************************************
\brief
	Set variables upon entering chase state
***********************************************************************/
void GuardVision::OnEnterChase()
{
	rotSpeed = 350.f;
}

/*!*********************************************************************
\brief
	Set the guard to look in the direction given by its rotation
***********************************************************************/
void GuardVision::FaceTowardsRotation()
{
	AEVec2 facingDir;
	AEVec2FromAngle(&facingDir, AEDegToRad(90.f + rotation));
	detector->SetFacingDir(facingDir);
}