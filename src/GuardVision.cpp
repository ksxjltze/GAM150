#include "GuardVision.h"
#include "Guard.h"
#include "BasicMeshShape.h"

using namespace StarBangBang;

GuardVision::GuardVision(GameObject* gameObject) 
	: Script(gameObject)
	, detected_player(false)
	, fieldOfView(70.f)
{
	player = nullptr;
	client = nullptr;
}

void GuardVision::Update()
{
	// update guard's vision stuff here
	AEVec2 defaultForward { 0, 1 };
	AEVec2 forwardVec, toPlayerVec, toClientVec;

	// calculate forward vector of guard
	//AEVec2Scale(&forwardVec, &defaultForward, gameObject->transform.rotation);
	AEVec2Normalize(&forwardVec, &forwardVec);

	// calculate vector from guard to player
	AEVec2Sub(&toPlayerVec, &gameObject->GetPos(), &player->GetPos());
	AEVec2Normalize(&toPlayerVec, &toPlayerVec);

	//PRINT("player pos: %f, %f\n", player->GetPos().x, player->GetPos().y);
	//PRINT("vec: %f, %f\n", toPlayerVec.x, toPlayerVec.y);
	float angle = acos(AEVec2DotProduct(&forwardVec, &toPlayerVec));
	angle = angle * 180 / PI;
	PRINT("angle: %f\n", angle);

	// temp cone vision
	DrawLine(300.f, gameObject->GetPos(), fieldOfView * 0.5f);
	DrawLine(300.f, gameObject->GetPos(), -fieldOfView * 0.5f);

	if (angle < (fieldOfView * 0.5f))
	{
		// raycast to check if vision is colliding with environment first
		// ...

		float viewDist = 250.f;
		//if (AEVec2SquareDistance(&player->GetPos(), &gameObject->GetPos()) <= viewDist * viewDist)
		{
			PRINT("%s\n", "DETECTED PLAYER");
			detected_player = true;
		}
	}

	if (detected_player)
	{
		// notify event manager: game over
	}
}