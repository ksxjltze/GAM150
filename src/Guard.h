/*!*********************************************************************
\title	  Captain Stealth
\file     Guard.h
\author   Liew Ruiheng Rayner (100%)
\par      DP email: r.liew\@digipen.edu
\date     10/04/2021

\brief
		  This file contains the Guard script class

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
***********************************************************************/

#pragma once
#include "ScriptComponent.h"
#include "GuardMovement.h"
#include "GuardVision.h"

namespace StarBangBang
{
	class Guard : public Script
	{
	public:
		enum class GUARD_STATE
		{
			STATE_NONE = 0,
			STATE_IDLE,
			STATE_PATROL,
			STATE_DISTRACTED,
			STATE_CHASE,
			STATE_TOTAL
		};

		/*!*********************************************************************
		\brief
			Non-default constructor

		\param gameObject
			The game object that will use this script
		***********************************************************************/
		Guard(GameObject* gameObject);

		/*!*********************************************************************
		\brief
			Sets up the script
		***********************************************************************/
		void Start();

		/*!*********************************************************************
		\brief
			Updates the script
		***********************************************************************/
		void Update();

		/*!*********************************************************************
		\brief
			Changes the guard's state

		\param _state
			The state the guard should change to
		***********************************************************************/
		void ChangeState(GUARD_STATE _state);

		/*!*********************************************************************
		\brief
			Retrieves the guard's current state

		\return
			The guard's current state
		***********************************************************************/
		inline GUARD_STATE GetState() const { return state; }

		/*!*********************************************************************
		\brief
			Retrieves the guard's previous state

		\return
			The guard's previous state
		***********************************************************************/
		inline GUARD_STATE GetPrevState() const { return prevState; }

		/*!*********************************************************************
		\brief
			Sets the guard's id

		\param
			The guard's id
		***********************************************************************/
		inline void SetID(size_t _id) { id = _id; }

		/*!*********************************************************************
		\brief
			Retrieves the guard's id

		\return
			The guard's id
		***********************************************************************/
		inline size_t GetID() const { return id; }

		/*!*********************************************************************
		\brief
			Set the room number that the guard is assigned to

		\param num
			The assigned room number
		***********************************************************************/
		inline void SetRoomNum(unsigned int num) { roomNum = num; }

		/*!*********************************************************************
		\brief
			Retrieves the guard's assigned room number

		\return
			The guard's assigned room number
		***********************************************************************/
		inline unsigned int GetRoomNum() const { return roomNum; }

	private:
		GUARD_STATE state;
		GUARD_STATE prevState;

		GuardMovement* movement;
		GuardVision* vision;
		size_t id;
		unsigned int roomNum;
	};
}

