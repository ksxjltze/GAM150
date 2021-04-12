/*!*********************************************************************
\title	  Captain Stealth
\file     GuardManager.cpp
\author   Liew Ruiheng Rayner (100%)
\par      DP email: r.liew\@digipen.edu
\date     10/04/2021

\brief
		  This file contains the function definitions of the 
		  GuardManager script class

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
***********************************************************************/

#include "GuardManager.h"
#include "ObjectManager.h"
#include "Sprite.h"
#include "Guard.h"
#include "Detector.h"
#include "GuardAnim.h"
#include "SecurityCamera.h"
#include "Physics.h"
#include "DistractionEvent.h"
#include "CaughtByCameraEvent.h"
#include "Text.h"
#include "globals.h"
#include "VisionCone.h"

using namespace StarBangBang;

/*!*********************************************************************
\brief
	Non-default constructor

\param gameObject
	The game object that will use this script
***********************************************************************/
GuardManager::GuardManager(GameObject* gameObject) 
	: Script(gameObject)
	, Listener()
{
}

/*!*********************************************************************
\brief
	Creates guards

\param objManager
	Pointer to the object manager

\param sprite
	Pointer to the guard sprite

\param player
	Pointer to the player game object

\param client
	Pointer to the client game object
***********************************************************************/
void GuardManager::CreateGuards(ObjectManager* objManager, Sprite* sprite, GameObject* player, GameObject* client)
{
	int id = 0;

	for (size_t i = 0; i < NUM_GUARDS; i++)
	{
		guards.push_back(objManager->NewGameObject());
		guards[i]->transform.scale = {0.7f, 0.7f};
		guards[i]->name = "Guard";
		objManager->AddImage(guards[i], *sprite);
		objManager->AddComponent<Guard>(guards[i]).SetID(i);
		objManager->AddComponent<GuardMovement>(guards[i]);
		objManager->AddComponent<GuardVision>(guards[i]);
		objManager->AddComponent<Detector>(guards[i]).Init(50.f, 250.f, player, client);
		objManager->AddComponent<RigidBody>(guards[i]);
		objManager->AddComponent<GuardAnim>(guards[i]);
		objManager->AddCollider(guards[i], false);
		objManager->AddComponent<VisionCone>(guards[i], 50.f, 250.f,20);
	}

	int roomNum = 1;
	SetGuardStartEnd(id++, roomNum, { -322, -1163 }, { -322, -596 });

	roomNum = 2;
	SetGuardStartEnd(id++, roomNum, { -72, -1162}, { -72, -385 });
	SetGuardStartEnd(id++, roomNum, { -42, -1203 }, { 1069, -1203 });
	SetGuardStartEnd(id++, roomNum, { 900, -1009 }, { 906, -456 });
	SetGuardStartEnd(id++, roomNum, { 466, -589 }, { 769, -589 });
	SetGuardStartEnd(id++, roomNum, { 314, -461 }, { 314, -954 });
	SetGuardStartEnd(id++, roomNum, { 751, -835 }, { 491, -853 });

	roomNum = 3;
	SetGuardStartEnd(id++, roomNum, { 945, -93 }, { 198, -93 });
	SetGuardStartEnd(id++, roomNum, { -225, -42 }, { -225, 296 });
	SetGuardStartEnd(id++, roomNum, { 0.1f, 850 }, { 0.1f, 500 });
	SetGuardStartEnd(id++, roomNum, { -13, 889 }, { 754, 895 });
	SetGuardStartEnd(id++, roomNum, { 1118, 68 }, { 1118, 671 });
	SetGuardStartEnd(id++, roomNum, { 330, 282 }, { 893, 282 });
	SetGuardStartEnd(id++, roomNum, { 783, 551 }, { 428, 551 });
	
	roomNum = 4;
	SetGuardStartEnd(id++, roomNum,{ -667, 1015 }, { -911, 1015 });
	SetGuardStartEnd(id++, roomNum,{ -849, 806 }, { -849, 949 });
	SetGuardStartEnd(id++, roomNum, { -1022, 651 }, { -715, 651 });
	SetGuardStartEnd(id++, roomNum, { -821, 544 }, { -821, 358 });
	SetGuardStartEnd(id++, roomNum, { -489, 972 }, { -489, 635 });
	SetGuardStartEnd(id++, roomNum, { -469, 382 }, { -469, 100 });
	SetGuardStartEnd(id++, roomNum, { -617, 175 }, { -617, 459 });
	SetGuardStartEnd(id++, roomNum, { -817, 47 }, { -1024, 47 });
	SetGuardStartEnd(id++, roomNum, { -1001, -100 }, { -1001, -300 });
}

/*!*********************************************************************
\brief
	Creates security cameras

\param objManager
	Pointer to the object manager

\param sprite
	Pointer to the security camera sprite

\param player
	Pointer to the player game object

\param client
	Pointer to the client game object
***********************************************************************/
void GuardManager::CreateSecurityCameras(ObjectManager* objManager, Sprite* sprite, GameObject* player, GameObject* client)
{
	int id = 0;

	for (size_t i = 0; i < NUM_CAMERAS; i++)
	{
		cameras.push_back(objManager->NewGameObject());
		cameras[i]->transform.scale = { 0.7f, 0.7f };
		objManager->AddImage(cameras[i], *sprite);
		objManager->AddComponent<SecurityCamera>(cameras[i]);
		objManager->AddComponent<Detector>(cameras[i]).Init(50.f, 300.f, player, client);
		objManager->AddComponent<VisionCone>(cameras[i], 50.f, 300.f, 20);
	}

	int roomNum = 1;
	InitSecurityCam(id++, roomNum,{ -300, -1200 }, 0.0f, 90.0f);
	roomNum = 2;
	InitSecurityCam(id++, roomNum, { 1150, -1200 }, -0.0f, 90.0f);
	roomNum = 3;
	InitSecurityCam(id++, roomNum,{450, -100},	0.0f, 90.0f);
	roomNum = 4;
	InitSecurityCam(id++, roomNum,{ 200, 700 }, -180.0f, -90.0f);
}

/*!*********************************************************************
\brief
	Handles event messages

\param e
	The event
***********************************************************************/
void GuardManager::onNotify(Event e)
{
	if (e.id == EventId::DISTRACTION)
	{
		DistractionEvent distraction = std::any_cast<DistractionEvent>(e.context);
		AEVec2 distractPos = distraction.gameObject->GetPos();
		GameObject* guard = GetNearestGuard(distractPos, distraction.roomNum);

		if (!guard)
		{
			std::cout << "No guard nearby/found\n";
			return;
		}

		std::cout << "Distraction Room Num: " << distraction.roomNum << std::endl;
		std::cout << "GUARD DISTRACTED! GUARD ID: " << guard->GetComponent<Guard>()->GetID() << std::endl;
		guard->GetComponent<GuardMovement>()->SetTargetPos(distractPos);
		guard->GetComponent<GuardMovement>()->SetDistractionDuration(distraction.duration);
		guard->GetComponent<Guard>()->ChangeState(Guard::GUARD_STATE::STATE_DISTRACTED);
	}

	if (e.id == EventId::CAUGHT_BY_CAMERA)
	{
		CaughtByCameraEvent event = std::any_cast<CaughtByCameraEvent>(e.context);
		AEVec2 eventPos = event.pos;
		GameObject* guard = GetNearestGuard(eventPos, event.roomNum);

		if (!guard)
		{
			std::cout << "No guard nearby/found\n";
			return;
		}

		std::cout << "CAUGHT BY CAMERA in Room Num: " << event.roomNum << std::endl;
		std::cout << "GUARD CHASING! GUARD ID: " << guard->GetComponent<Guard>()->GetID() << std::endl;
		guard->GetComponent<GuardMovement>()->SetTargetPos(eventPos);
		guard->GetComponent<Guard>()->ChangeState(Guard::GUARD_STATE::STATE_CHASE);
	}
}

/*!*********************************************************************
\brief
	Retrieves the guard game object in the given room which is
	closest to the given position

\param _pos
	The position to check if near to

\param roomNum
	The room number to look for guards

\return
	The guard game object that is closest
***********************************************************************/
GameObject* GuardManager::GetNearestGuard(const AEVec2& _pos, unsigned int roomNum)
{
	AEVec2 distractionPos = _pos;
	float minDist = 999999.f;
	GameObject* nearestGuard = nullptr;

	for (size_t i = 0; i < NUM_GUARDS; i++)
	{
		Guard* guard = guards[i]->GetComponent<Guard>();

		// only look for guards not currently distracted
		if (guard->GetState() == Guard::GUARD_STATE::STATE_DISTRACTED)
			continue;

		// only look for guards in same room as object
		if (guard->GetRoomNum() != roomNum)
			continue;

		float dist = AEVec2SquareDistance(&distractionPos, &guards[i]->transform.position);

		if (dist < minDist)
		{
			minDist = dist;
			nearestGuard = guards[i];
		}
	}

	return nearestGuard;
}

/*!*********************************************************************
\brief
	Sets 2 points for the guards to patrol at a given speed. Also assigns
	the room number to the guards.

\param id
	The id of the guard

\param roomNum
	The room number that the guard is assigned to

\param start
	The start of the patrol route

\param end
	The end of the patrol route

\param isIdle
	Whether the guard is an idle guard (doesn't patrol)

\param speed
	The movement speed of the guard
***********************************************************************/
void GuardManager::SetGuardStartEnd(int id, unsigned int roomNum, const AEVec2& start, const AEVec2& end, bool isIdle, float speed)
{
	guards[id]->GetComponent<Guard>()->SetRoomNum(roomNum);
	guards[id]->GetComponent<GuardMovement>()->SetSpeed(speed);
	guards[id]->GetComponent<GuardMovement>()->SetStartEndPos(start, end, isIdle);

	if (isIdle)
	{
		guards[id]->GetComponent<Guard>()->ChangeState(Guard::GUARD_STATE::STATE_IDLE);
	}
}

/*!*********************************************************************
\brief
	Sets a collection of points for the guards to patrol at a given speed.
	Also assigns the room number to the guards.

\param id
	The id of the guard

\param roomNum
	The room number that the guard is assigned to

\param waypoints
	The list of points of the patrol route

\param speed
	The movement speed of the guard
***********************************************************************/
void GuardManager::SetGuardWaypoints(int id, unsigned int roomNum, const std::vector<AEVec2>& waypoints, float speed)
{
	guards[id]->GetComponent<Guard>()->SetRoomNum(roomNum);
	guards[id]->GetComponent<GuardMovement>()->SetSpeed(speed);
	guards[id]->GetComponent<GuardMovement>()->SetWaypoints(waypoints);
	guards[id]->SetPos(waypoints.front());
}

/*!*********************************************************************
\brief
	Sets the rotation angles that the camera will rotate between at a
	given speed. Also assigns the room number to it.

\param id
	The id of the camera

\param roomNum
	The room number that the camera is assigned to

\param pos
	The position of the camera

\param min
	The minimum rotation angle

\param max
	The maximum rotation angle

\param speed
	The rotation speed of the camera
***********************************************************************/
void GuardManager::InitSecurityCam(int id, unsigned int roomNum, const AEVec2& pos, float min, float max, float speed)
{
	cameras[id]->SetPos(pos);
	cameras[id]->GetComponent<SecurityCamera>()->SetRoomNum(roomNum);
	cameras[id]->GetComponent<SecurityCamera>()->SetRotationMinMax(min, max);
	cameras[id]->GetComponent<SecurityCamera>()->SetRotSpeed(speed);
}