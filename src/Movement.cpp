/******************************************************************************/
/*!
\title		Captain Stealth
\file		Movement.cpp
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Movement script.
			Directly translates the game object using WASD.

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/

#include "Movement.h"
#include "globals.h"

/*!*************************************************************************
 * \brief
 * Script Constructor.
 * Attaches the script to a game object
 * \param gameObject
 * GameObject to attach to.
***************************************************************************/
StarBangBang::Movement::Movement(GameObject* gameObject) : Script(gameObject)
{

}

/*!*************************************************************************
 * \brief
 * Start function. Called once at the start of the scene.
 * \return
 * void
***************************************************************************/
void StarBangBang::Movement::Start()
{

}

/*!*************************************************************************
 * \brief
 * Update function. Called once per frame.
 * \return
 * void
***************************************************************************/
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
