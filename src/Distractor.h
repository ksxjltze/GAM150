/*!*********************************************************************
\title	  Captain Stealth
\file     Distractor.h
\author   Sim Chin Hin
\par      DP email: s.chinhin\@digipen.edu
\date     11/04/2021

\brief
		  This file contains the Distractor script class

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
***********************************************************************/
#pragma once
#include "ScriptComponent.h"
#include "Listener.h"

namespace StarBangBang
{
	class Distractor : public Script, public Listener
	{
	public:
		/*!*********************************************************************
		\brief
			Distractor constructor
		\param	gameObject
			gameObject that will be used
		***********************************************************************/
		Distractor(GameObject* gameObject);
		/*!*********************************************************************
		\brief
			Start state of the distractor
		***********************************************************************/
		void Start();
		/*!*********************************************************************
		\brief
			Update distractor's current state
		***********************************************************************/
		void Update();
		/*!*********************************************************************
		\brief
			Update distractor's time and animation when activated
		***********************************************************************/
		void onNotify(Event e);
		/*!*********************************************************************
		\brief
			Sends distraction event to guards 
		***********************************************************************/
		void SendDistractionEvent();

		/*!*********************************************************************
		\brief
			Set room number for each distractor
		***********************************************************************/
		inline void SetRoomNum(unsigned int num) { roomNum = num; }
		/*!*********************************************************************
		\brief
			Get room number for each room
		\return
			int room number
		***********************************************************************/
		inline unsigned int GetRoomNum() const { return roomNum; }
		/*!*********************************************************************
		\brief
			Get duration of the distractor
		\return
			float duration
		***********************************************************************/
		inline float GetDuration() const { return duration; }

	private:
		bool activated;
		float duration;
		float timer;
		float scaleTimer;
		float scaleTimerY = 0.f;
		unsigned int roomNum;
	};
}
