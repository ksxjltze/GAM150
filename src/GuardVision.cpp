#include "GuardVision.h"
#include "Guard.h"
#include "BasicMeshShape.h"

using namespace StarBangBang;

GuardVision::GuardVision(GameObject* gameObject) 
	: Script(gameObject)
	, detected_player(false)
	, fieldOfView(90.f)
	, viewDist(250.f)
	, player(nullptr)
	, client(nullptr)
{
}

void GuardVision::Update()
{
	// only update if player or client in same partition grid as guard
	// ...

	AEVec2 defaultForward { 0, 1 }; // up
	AEVec2 forwardVec, toPlayerVec, toClientVec;

	// calculate forward vector of guard after rotation
	// ...

	// calculate vector from guard to player
	AEVec2Sub(&toPlayerVec, &player->GetPos(), &gameObject->GetPos());
	AEVec2Normalize(&toPlayerVec, &toPlayerVec);
	
	float dpResult = AEVec2DotProduct(&defaultForward, &toPlayerVec);
	if (dpResult <= 0.f) // don't continue if target is behind guard
	{
		//return;
	}

	float angle = AEACos(dpResult);
	angle = AERadToDeg(angle);

	// temp cone vision
	DrawLine(viewDist + 50.f, gameObject->GetPos(), fieldOfView * 0.5f);
	DrawLine(viewDist + 50.f, gameObject->GetPos(), -fieldOfView * 0.5f);

	if (AEVec2SquareDistance(&player->GetPos(), &gameObject->GetPos()) <= viewDist * viewDist)
	{
		if (angle < (fieldOfView * 0.5f))
		{
			// check if vision is colliding with environment first
			// ...

			PRINT("%s\n", "DETECTED PLAYER");
			detected_player = true;
		}
		else
			PRINT("WHERE PLAYER\n");
	}
	else
		PRINT("WHERE PLAYER\n");

	if (detected_player)
	{
		// notify event manager: game over
	}
}