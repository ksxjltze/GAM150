/*!*********************************************************************
\title	  Captain Stealth
\file     SecurityCamera.h
\author   Liew Ruiheng Rayner (100%)
\par      DP email: r.liew\@digipen.edu
\date     10/04/2021

\brief
		  This file contains the SecurityCamera script class

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
***********************************************************************/

#pragma once
#include "ScriptComponent.h"

namespace StarBangBang
{
	class Detector;

	class SecurityCamera : public Script
	{
	public:
		/*!*********************************************************************
		\brief
			Non-default constructor

		\param gameObject
			The game object that will use this script
		***********************************************************************/
		SecurityCamera(GameObject* gameObject);

		/*!*********************************************************************
		\brief
			Sets up the script
		***********************************************************************/
		void Start();

		/*!*********************************************************************
		\brief
			Updates the script. Rotates camera's vision to look in the direction
			given by its rotation.
		***********************************************************************/
		void Update();

		/*!*********************************************************************
		\brief
			Sets the rotation angles to rotate between
		
		\param _minRot
			The minimum rotation

		\param _maxRot
			The maximum rotation
		***********************************************************************/
		void SetRotationMinMax(float _minRot, float _maxRot);

		/*!*********************************************************************
		\brief
			Sets the rotation speed

		\param _speed
			The rotation speed
		***********************************************************************/
		inline void SetRotSpeed(float _speed) { rotSpeed = _speed; }

		/*!*********************************************************************
		\brief
			Sets the room number this camera is assigned to

		\param num
			The room number
		***********************************************************************/
		inline void SetRoomNum(unsigned int num) { roomNum = num; }

		/*!*********************************************************************
		\brief
			Gets the room number this camera is assigned to

		\return
			The room number this camera is assigned to
		***********************************************************************/
		inline unsigned int GetRoomNum() const { return roomNum; }

	private:
		bool detected;
		unsigned int roomNum;
		float minRot, maxRot;
		float rotSpeed;

		Detector* detector;
	};
}