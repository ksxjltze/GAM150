/******************************************************************************/
/*!
\title		Captain Stealth
\file		PrimaryMovementController.cpp
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Primary Movement Controller script.
			Allows the gameObject to move around with WASD and Arrow keys.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#include "PrimaryMovementController.h"
#include "constants.h"
float speed = 50.0f;
AEVec2 movement = AEVec2{0,0};
StarBangBang::PrimaryMovementController::PrimaryMovementController(GameObject* gameObject) : Script(gameObject), rb{nullptr}
{

}

void StarBangBang::PrimaryMovementController::Start()
{
	rb = gameObject->GetComponent<RigidBody>();
	rb->drag = 0.2f;
}

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
