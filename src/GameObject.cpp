/******************************************************************************/
/*!
\title		Captain Stealth
\file		GameObject.cpp
\author 	Lee Jia Keat
\par    	email: l.jiakeat@digipen.edu
\date   	April 09, 2021
\brief		GameObject class. Smallest element of the game.
			Contains a Transform struct and a list of components.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#include "GameObject.h"
#include "constants.h"

StarBangBang::GameObject::GameObject()
{
	active = true;
	transform.scale = { CONSTANTS::DEFAULT_OBJECT_SCALE,  CONSTANTS::DEFAULT_OBJECT_SCALE };
	transform.rotation = 0;
	transform.position = { 0, 0 };
}

StarBangBang::GameObject::GameObject(const GameObject& obj)
{
	transform = obj.transform;
	parent = obj.parent;
	active = obj.active;
}

AEVec2 StarBangBang::GameObject::GetPos()
{
	if (parent != nullptr)
	{
		AEVec2 pos;
		AEVec2Add(&pos, &parent->transform.position, &transform.position);
		return pos;
	}
	return transform.position;
}

void StarBangBang::GameObject::SetPos(AEVec2 newPos)
{
	{
		if (parent != nullptr)
		{
			AEVec2 pos;
			AEVec2Sub(&pos, &newPos, &parent->transform.position);
			transform.position = pos;
		}
		else
			transform.position = newPos;
	}
}

void StarBangBang::GameObject::SetActive(bool status)
{
	active = status;
}
