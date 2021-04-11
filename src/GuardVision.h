/*!*********************************************************************
\title	  Captain Stealth
\file     GuardVision.h
\author   Liew Ruiheng Rayner (100%)
\par      DP email: r.liew\@digipen.edu
\date     10/04/2021

\brief
		  This file contains the GuardVision script class

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
***********************************************************************/

#pragma once
#include "ScriptComponent.h"

namespace StarBangBang
{
	class GuardMovement;
	class Detector;

	class GuardVision : public Script
	{
	public:
		/*!*********************************************************************
		\brief
			Non-default constructor

		\param gameObject
			The game object that will use this script
		***********************************************************************/
		GuardVision(GameObject* gameObject);

		/*!*********************************************************************
		\brief
			Sets up the script
		***********************************************************************/
		void Start();

		/*!*********************************************************************
		\brief
			Updates the script. Rotates guard's vision to look in the direction
			of the next position it is going to.
		***********************************************************************/
		void Update();

		/*!*********************************************************************
		\brief
			Set variables upon entering idle state
		***********************************************************************/
		void OnEnterIdle();

		/*!*********************************************************************
		\brief
			Guard's idle vision behaviour
		***********************************************************************/
		void Idle();

		/*!*********************************************************************
		\brief
			Set variables upon entering patrol state
		***********************************************************************/
		void OnEnterPatrol();

		/*!*********************************************************************
		\brief
			Set variables upon entering distracted state
		***********************************************************************/
		void OnEnterDistracted();

		/*!*********************************************************************
		\brief
			Set variables upon entering chase state
		***********************************************************************/
		void OnEnterChase();

		/*!*********************************************************************
		\brief
			Get detector

		\return
			The detector
		***********************************************************************/
		inline Detector* GetDetector() { return detector; }

		/*!*********************************************************************
		\brief
			Set the guard's vision rotation speed

		\param speed
			Speed of the rotation
		***********************************************************************/
		inline void SetRotationSpeed(float speed) { rotSpeed = speed; }

	private:
		/*!*********************************************************************
		\brief
			Set the guard to look in the direction given by its rotation
		***********************************************************************/
		void FaceTowardsRotation();

		GuardMovement* movement;
		Detector* detector;

		float rotation;
		float rotSpeed;
		float idleDuration;
		int prevRot, currRot;

		bool turn;
	};
}