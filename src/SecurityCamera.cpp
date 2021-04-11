/*!*********************************************************************
\title	  Captain Stealth
\file     SecurityCamera.cpp
\author   Liew Ruiheng Rayner (100%)
\par      DP email: r.liew\@digipen.edu
\date     10/04/2021

\brief
		  This file contains the function definitions of
		  SecurityCamera script class

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
***********************************************************************/

#include "SecurityCamera.h"
#include "Detector.h"
#include "MessageBus.h"
#include "CaughtByCameraEvent.h"

using namespace StarBangBang;

/*!*********************************************************************
\brief
	Non-default constructor

\param gameObject
	The game object that will use this script
***********************************************************************/
SecurityCamera::SecurityCamera(GameObject* gameObject)
	: Script(gameObject)
	, roomNum(0)
	, minRot(0.f)
	, maxRot(0.f)
	, rotSpeed(GUARD::CAM_ROT_SPEED)
	, detector(nullptr)
	, detected(false)
{
}

/*!*********************************************************************
\brief
	Sets up the script
***********************************************************************/
void SecurityCamera::Start()
{
	detector = gameObject->GetComponent<Detector>();
}

/*!*********************************************************************
\brief
	Updates the script. Rotates camera's vision to look in the direction
	given by its rotation.
***********************************************************************/
void SecurityCamera::Update()
{
	detector->SpanVision(minRot, maxRot, rotSpeed);
	gameObject->transform.rotation = detector->GetRotation();

	if (detected)
		return;

	AEVec2 targetPos;
	if (detector->GetDetected(targetPos))
	{
		MessageBus::Notify({ EventId::PRINT_TEXT, std::string("DETECTED!") });
		CaughtByCameraEvent e{ gameObject };
		e.pos = targetPos;
		e.roomNum = roomNum;
		e.SendEvent();
		detected = true;
	}
}

/*!*********************************************************************
\brief
	Sets the rotation angles to rotate between

\param _minRot
	The minimum rotation

\param _maxRot
	The maximum rotation
***********************************************************************/
void SecurityCamera::SetRotationMinMax(float _minRot, float _maxRot)
{
	minRot = _minRot;
	maxRot = _maxRot;

	if (!detector)
		detector = gameObject->GetComponent<Detector>();

	detector->Rotate(maxRot);
}