#include "GuardVision.h"
#include "Guard.h"
#include"GuardMovement.h"
#include "BasicMeshShape.h"
#include "Utils.h"

using namespace StarBangBang;

GuardVision::GuardVision(GameObject* gameObject) 
	: Script(gameObject)
	, detected_player(false)
	, fieldOfView(90.f)
	, viewDist(250.f)
	, player(nullptr)
	, client(nullptr)
	, movement(nullptr)
	, defaultForward({ 0, 1 })
{
}

void GuardVision::Start()
{
	movement = gameObject->GetComponent<GuardMovement>();
}

void GuardVision::Update()
{
	// only update if player or client in same partition grid as guard
	// ...
	// 
	
	AEVec2 forwardVec, toPlayerVec, toClientVec;
	AEVec2 go_pos = gameObject->GetPos();

	if (movement->IsMoving())
	{
		// rotate guard's vision
		AEVec2 targetPos = gameObject->GetComponent<GuardMovement>()->GetNextPos();
		AEVec2Sub(&targetDir, &targetPos, &go_pos);
		AEVec2Normalize(&targetDir, &targetDir);

		visionRot = AERadToDeg(AEACos(AEVec2DotProduct(&defaultForward, &targetDir)));
		if (targetPos.x > gameObject->GetPos().x)
			visionRot *= -1;
	}
	else
	{
		visionRot = 0.f;
	}

	DrawVision();

	//PRINT("%f\n", visionRot);

	AEVec2 p_pos = player->GetPos();

	// calculate vector from guard to player
	AEVec2Sub(&toPlayerVec, &p_pos, &go_pos);
	AEVec2Normalize(&toPlayerVec, &toPlayerVec);

	float dpResult = AEVec2DotProduct(&targetDir, &toPlayerVec);
	if (dpResult < 0.f) // don't continue if target is behind guard
		return;

	float angle = AEACos(dpResult);
	angle = AERadToDeg(angle);

	if (AEVec2SquareDistance(&p_pos, &go_pos) <= viewDist * viewDist)
	{
		if (angle < (fieldOfView * 0.5f))
		{
			// check if vision is colliding with environment first
			// ...

			//PRINT("%s\n", "DETECTED PLAYER");
			detected_player = true;
		}
		//else
			//PRINT("WHERE PLAYER\n");
	}
	//else
		//PRINT("WHERE PLAYER\n");

	if (detected_player)
	{
		// notify event manager: game over
	}
}

void GuardVision::DrawVision()
{
	DrawLine(viewDist + 50.f, gameObject->GetPos(), (fieldOfView * 0.5f) + visionRot);
	DrawLine(viewDist + 50.f, gameObject->GetPos(), (-fieldOfView * 0.5f) + visionRot);
}