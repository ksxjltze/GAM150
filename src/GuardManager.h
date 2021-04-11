/*!*********************************************************************
\title	  Captain Stealth
\file     GuardManager.h
\author   Liew Ruiheng Rayner (100%)
\par      DP email: r.liew\@digipen.edu
\date     10/04/2021

\brief
		  This file contains the GuardManager script class

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
***********************************************************************/

#pragma once
#include "ScriptComponent.h"
#include "ObjectManager.h"
#include "Guard.h"
#include "Listener.h"
#include <vector>

namespace StarBangBang
{
	class ObjectManager;
	struct Sprite;

	class GuardManager : public Script, Listener
	{
	private:
		const unsigned int NUM_GUARDS = 23;
		const unsigned int NUM_CAMERAS = 4;

	public:
		/*!*********************************************************************
		\brief
			Non-default constructor

		\param gameObject
			The game object that will use this script
		***********************************************************************/
		GuardManager(GameObject* gameObject);

		/*!*********************************************************************
		\brief
			Sets up the script
		***********************************************************************/
		void Start() {};

		/*!*********************************************************************
		\brief
			Updates the script
		***********************************************************************/
		void Update() {};

		/*!*********************************************************************
		\brief
			Handles event messages

		\param e
			The event
		***********************************************************************/
		void onNotify(Event e);

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
		void CreateGuards(ObjectManager* objManager, Sprite* sprite, GameObject* player, GameObject* client);

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
		void CreateSecurityCameras(ObjectManager* objManager, Sprite* sprite, GameObject* player, GameObject* client);

		/*!*********************************************************************
		\brief
			Retrieves the list of guard game objects

		\return
			The vector container of guard game objects
		***********************************************************************/
		std::vector<GameObject*> GetGuards() const { return guards; }

	private:
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
		GameObject* GetNearestGuard(const AEVec2& _pos, unsigned int roomNum);

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
		void SetGuardStartEnd(int id, unsigned int roomNum, const AEVec2& start, const AEVec2& end, bool isIdle = false, float speed = GUARD::GUARD_SPEED);

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
		void SetGuardWaypoints(int id, unsigned int roomNum, const std::vector<AEVec2>& waypoints, float speed = GUARD::GUARD_SPEED);

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
		void InitSecurityCam(int id, unsigned int roomNum, const AEVec2& pos, float min, float max, float speed = GUARD::CAM_ROT_SPEED);

		std::vector<GameObject*> guards;
		std::vector<GameObject*> cameras;
	};
}