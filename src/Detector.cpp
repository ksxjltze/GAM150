/*!*********************************************************************
\title	  Captain Stealth
\file     Detector.cpp
\author   Liew Ruiheng Rayner
\par      DP email: r.liew\@digipen.edu
\date     10/04/2021

\brief
		  This file contains the function definitions of Detector
		  script class

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
***********************************************************************/

#include "Detector.h"
#include "BasicMeshShape.h"
#include "globals.h"
#include "MessageBus.h"
#include "CollisionManager.h"
#include "PlayerScript.h"

using namespace StarBangBang;

/*!*********************************************************************
\brief
	Non-default constructor

\param gameObject
	The game object that will use this script
***********************************************************************/
Detector::Detector(GameObject* gameObject)
	: Script(gameObject)
	, fieldOfView(0.f)
	, viewDist(0.f)
	, target1(nullptr)
	, target2(nullptr)
	, target1Col(nullptr)
	, target2Col(nullptr)
	, myCollider(nullptr)
	, player(nullptr)
	, rotationAngle(0.f)
	, atMaxRot(false)
	, detectedTarget1(false)
	, detectedTarget2(false)
	, defaultForward({ 0, 1 })
	, targetDir({ 0, 1 })
{
}

/*!*********************************************************************
\brief
	Sets up the script
***********************************************************************/
void Detector::Start()
{
	player = target1->GetComponent<PlayerScript>();
}

/*!*********************************************************************
\brief
	Updates the script
***********************************************************************/
void Detector::Update()
{
	if (detectedTarget1 || detectedTarget2)
		color = Red;
	//else if (!detectedTarget1 && !detectedTarget2)
	//	color = White;

	if (!player->isInvisible())
	{
		if (target1->active && target1->visible)
			CheckForTargets(target1->GetPos());

	}
	if (target2->active && target2->visible)
		CheckForTargets(target2->GetPos(), false);
}

/*!*********************************************************************
\brief
	Initializes the detector

\param fov
	The field of view

\param range
	The range of the detector

\param _player
	Pointer to the player game object

\param client
	Pointer to the client game object
***********************************************************************/
void Detector::Init(float fov, float range, GameObject* _player, GameObject* client)
{
	fieldOfView = fov;
	viewDist = range;
	target1 = _player;
	target2 = client;
	target1Col = target1->GetComponent<BoxCollider>();
	target2Col = target2->GetComponent<BoxCollider>();
	myCollider = gameObject->GetComponent<BoxCollider>();
}

/*!*********************************************************************
\brief
	Rotates the detector and its vision cone

\param angle
	The amount of rotation
***********************************************************************/
void Detector::Rotate(float angle)
{
	rotationAngle = angle;
}

/*!*********************************************************************
\brief
	Rotates the detector between 2 given angles at a given speed

\param minRot
	The first angle

\param maxRot
	The second angle

\param speed
	Rotation speed
***********************************************************************/
void Detector::SpanVision(float minRot, float maxRot, float speed)
{
	if (!atMaxRot && rotationAngle <= maxRot)
	{
		rotationAngle += static_cast<float>(g_dt) * speed;
	}
	else
	{
		atMaxRot = true;
	}

	if (atMaxRot && rotationAngle >= minRot)
	{
		rotationAngle -= static_cast<float>(g_dt) * speed;
	}
	else
	{
		atMaxRot = false;
	}

	AEVec2 facingDir;
	AEVec2FromAngle(&facingDir, AEDegToRad(90.f + rotationAngle));
	targetDir = facingDir;
}

/*!*********************************************************************
\brief
	Using the detector's field of view and viewing range, check if
	a given target position has been detected

\param _targetPos
	The target position to check for

\param checkForPlayer
	Set if detector is checking for the player game object
***********************************************************************/
void Detector::CheckForTargets(const AEVec2& _targetPos, bool checkForPlayer)
{
	BoxCollider* collider = nullptr;

	if (checkForPlayer)
		collider = target1Col;
	else
		collider = target2Col;
	
	AEVec2 toTargetVec;
	AEVec2 goPos = gameObject->GetPos();
	AEVec2 targetPos = _targetPos;

	// calculate vector from game object to target
	AEVec2Sub(&toTargetVec, &targetPos, &goPos);
	AEVec2Normalize(&toTargetVec, &toTargetVec);

	float dpResult = AEVec2DotProduct(&targetDir, &toTargetVec);
	if (dpResult < 0.f) // don't continue if target is behind detector
	{
		if (checkForPlayer)
			detectedTarget1 = false;
		else
			detectedTarget2 = false;

		return;
	}

	float angle = AEACos(dpResult);
	angle = AERadToDeg(angle);

	if (AEVec2SquareDistance(&targetPos, &goPos) <= viewDist * viewDist)
	{
		if (angle < (fieldOfView * 0.5f))
		{
			// check if vision is colliding with environment first
			Ray ray = Ray(gameObject->GetPos(), _targetPos);

			if (CollisionManager::LineCast(ray, myCollider) == collider)
			{
				SetDetected(checkForPlayer, true);

				//Event test
				if (detectedTarget1)
					MessageBus::Notify({ EventId::DETECTED, target1 });
				else if (detectedTarget2)
					MessageBus::Notify({ EventId::DETECTED, target2 });
			}
			else
			{
				SetDetected(checkForPlayer, false);
			}
		}
		else
		{
			SetDetected(checkForPlayer, false);
		}
	}
	else
	{
		SetDetected(checkForPlayer, false);
	}
}

/*!*********************************************************************
\brief
	Sets the appropriate detected boolean to true according to the
	detected game object

\param checkForPlayer
	Set if player is detected

\param detected
	Whether the game object has been detected
***********************************************************************/
void Detector::SetDetected(bool checkForPlayer, bool detected)
{
	if (checkForPlayer)
		detectedTarget1 = detected;
	else
		detectedTarget2 = detected;
}

/*!*********************************************************************
\brief
	Checks if a given target position has been detected

\param targetPos
	The position to check for

\return
	Whether the target position was detected
***********************************************************************/
bool Detector::GetDetected(AEVec2& targetPos) const
{
	if (detectedTarget1)
	{
		targetPos = target1->GetPos();
	}
	else if (detectedTarget2)
	{
		targetPos = target2->GetPos();
	}

	return (detectedTarget1 || detectedTarget2);
}