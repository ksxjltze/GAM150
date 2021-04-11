/******************************************************************************/
/*!
\title		Captain Stealth
\file		Movement.cpp
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Movement script.
			Directly translates the game object using WASD.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#include "Movement.h"
#include "globals.h"

StarBangBang::Movement::Movement(GameObject* gameObject) : Script(gameObject)
{

}

void StarBangBang::Movement::Start()
{

}

void StarBangBang::Movement::Update()
{
	
	float speed = PLAYER::PLAYER_SPEED * g_dt;
	if (AEInputCheckCurr(AEVK_W))
	{
		gameObject->transform.position.y += speed;
	}

	if (AEInputCheckCurr(AEVK_A))
	{
		gameObject->transform.position.x += -speed;
	}

	if (AEInputCheckCurr(AEVK_S))
	{
		gameObject->transform.position.y += -speed;
	}

	if (AEInputCheckCurr(AEVK_D))
	{
		gameObject->transform.position.x += speed;
	}

}
