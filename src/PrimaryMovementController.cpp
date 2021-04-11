/******************************************************************************/
/*!
\title		Captain Stealth
\file		PrimaryMovementController.h
\author 	Lee Jia Keat
			Created the file and setup input flow.
\par    	email: l.jiakeat\@digipen.edu

\author2	Ho Yi Guan
			Integrated RigidBody mechanics.
\par		email: yiguan.ho@digipen.edu

\date   	April 09, 2021
\brief		Primary Movement Controller script.
			Allows the gameObject to move around with WASD and Arrow keys.

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/

#include "PrimaryMovementController.h"
#include "constants.h"
float speed = 50.0f;
AEVec2 movement = AEVec2{0,0};

/*!*************************************************************************
 * \brief
 * Script constructor.
 * Attaches the script to a game object
 * \param gameObject
 * GameObject to attach to.
***************************************************************************/
StarBangBang::PrimaryMovementController::PrimaryMovementController(GameObject* gameObject) : Script(gameObject), rb{nullptr}
{

}

/*!*************************************************************************
 * \brief
 * Start.
 * \return
 * void
***************************************************************************/
void StarBangBang::PrimaryMovementController::Start()
{
	rb = gameObject->GetComponent<RigidBody>();
	rb->drag = 0.2f;
}

/*!*************************************************************************
 * \brief
 * Update.
 * \return
 * void
***************************************************************************/
void StarBangBang::PrimaryMovementController::Update()
{
	using namespace KEYBIND;

	float h = 0.0f, v = 0.0f;

	if (AEInputCheckCurr(MOVEMENT_UP) || AEInputCheckCurr(MOVEMENT_UP_ALT))
		v = 1;
	
	if (AEInputCheckCurr(MOVEMENT_DOWN) || AEInputCheckCurr(MOVEMENT_DOWN_ALT))
		v = -1;

	if (AEInputCheckCurr(MOVEMENT_LEFT) || AEInputCheckCurr(MOVEMENT_LEFT_ALT))
		h = -1;
	
	if (AEInputCheckCurr(MOVEMENT_RIGHT) || AEInputCheckCurr(MOVEMENT_RIGHT_ALT))
		h = 1;
	
	movement.x = h * speed;
	movement.y = v * speed;

	rb->AddVelocity(movement, 1.0f);
}
