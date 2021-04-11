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
	AEVec2 GetMouseWorldPos(bool isWorld = true);
	bool CompareGameObject(GameObject* A, GameObject* B);
	bool PointRectTest(AEVec2 pointPos, AEVec2 rectCenter, float width, float height);
}