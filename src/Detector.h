/*!*********************************************************************
\title	  Captain Stealth
\file     Detector.h
\author   Liew Ruiheng Rayner
\par      DP email: r.liew\@digipen.edu
\date     10/04/2021

\brief
          This file contains the Detector script class

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
***********************************************************************/

#pragma once
#include "ScriptComponent.h"
#include "Color.h"
#include "PlayerScript.h"

namespace StarBangBang
{
	class BoxCollider;

	class Detector : public Script
	{
	public:
		/*!*********************************************************************
		\brief
			Non-default constructor

		\param gameObject
			The game object that will use this script
		***********************************************************************/
		Detector(GameObject* gameObject);

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
		void Init(float fov, float range, GameObject* _player, GameObject* client);

		/*!*********************************************************************
		\brief
			Rotates the detector and its vision cone

		\param angle
			The amount of rotation
		***********************************************************************/
		void Rotate(float angle);

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
		void SpanVision(float minRot, float maxRot, float speed);

		/*!*********************************************************************
		\brief
			Sets the rotation angle (degrees)

		\param angle
			The rotation angle in degrees
		***********************************************************************/
		inline void SetAngle(float angle) { rotationAngle = angle; }

		/*!*********************************************************************
		\brief
			Sets the detector's direction to face

		\param dir
			The direction to look at
		***********************************************************************/
		inline void SetFacingDir(const AEVec2& dir) { targetDir = dir; }

		/*!*********************************************************************
		\brief
			Retrieves the rotation angle (degrees)

		\return
			The rotation angle in degrees
		***********************************************************************/
		inline float GetRotation() const { return rotationAngle; }

		/*!*********************************************************************
		\brief
			Checks if a given target position has been detected

		\param targetPos
			The position to check for

		\return
			Whether the target position was detected
		***********************************************************************/
		bool GetDetected(AEVec2& targetPos) const;
		
		/*!*********************************************************************
		\brief
			Retrieves the color of the detector's vision cone

		\return
			The color of the vision cone
		***********************************************************************/
		inline const Color& GetColor() const { return color; }

	private:
		/*!*********************************************************************
		\brief
			Using the detector's field of view and viewing range, check if
			a given target position has been detected

		\param _targetPos
			The target position to check for

		\param checkForPlayer
			Set if detector is checking for the player game object
		***********************************************************************/
		void CheckForTargets(const AEVec2& _targetPos, bool checkForPlayer = true);

		/*!*********************************************************************
		\brief
			Sets the appropriate detected boolean to true according to the
			detected game object

		\param checkForPlayer
			Set if player is detected

		\param detected
			Whether the game object has been detected
		***********************************************************************/
		void SetDetected(bool checkForPlayer, bool detected);

		float fieldOfView;
		float viewDist;
		float rotationAngle;

		bool atMaxRot;

		bool detectedTarget1, detectedTarget2;

		AEVec2 defaultForward;
		AEVec2 targetDir;

		GameObject* target1, *target2;
		BoxCollider* target1Col, *target2Col;
		BoxCollider* myCollider;

		PlayerScript* player;

		Color color;
	};
}