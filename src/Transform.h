/******************************************************************************/
/*!
\title		Captain Stealth
\file		Transform.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Transform struct. Contains data representing the game object's position in the world.
			i.e. The position, scale and rotation of the game object.

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/

#pragma once
#include "AEEngine.h"

namespace StarBangBang
{
	struct Transform
	{
		AEVec2 position, scale;
		float rotation;
	};
}