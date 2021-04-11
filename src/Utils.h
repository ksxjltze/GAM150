/******************************************************************************/
/*!
\title		Captain Stealth
\file		Utils.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Global Utility functions.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "AEEngine.h"
#include "GameObject.h"
//Helper functions

namespace StarBangBang
{
	/*!*************************************************************************
	 * \brief 
	 * Gets the position of the mouse.
	 * \param isWorld
	 * True to get the world position of the mouse with respect to camera.
	 * False to ignore camera.
	 * \return
	 * Position of the mouse.
	***************************************************************************/
	AEVec2 GetMouseWorldPos(bool isWorld = true);

	/*!*************************************************************************
	 * \brief 
	 * Compares two game objects by their horizontal position
	 * \param A
	 * First game object.
	 * \param B
	 * Second game object.
	 * \return
	 * True if A's horizontal position is less than B's horionzontal position.
	 * False otherwise.
	***************************************************************************/
	bool CompareGameObject(GameObject* A, GameObject* B);

	/*!*************************************************************************
	 * \brief 
	 * Tests if a point is inside a rect.
	 * \param pointPos
	 * Position of the point.
	 * \param rectCenter
	 * Position of the center of the rect.
	 * \param width
	 * Width of the rect.
	 * \param height
	 * height of the rect.
	 * \return
	 * True if the point is inside the rect.
	 * False otherwise.
	***************************************************************************/
	bool PointRectTest(AEVec2 pointPos, AEVec2 rectCenter, float width, float height);
}