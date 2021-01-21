#include "SecondaryMovementController.h"
#include "Utils.h"
#include "constants.h"

void StarBangBang::SecondaryMovementController::Start()
{
	targetPos = gameObject->transform.position;
}

void StarBangBang::SecondaryMovementController::Update()
{
	float dt = (float)AEFrameRateControllerGetFrameTime();
	AEVec2* currentPos = &gameObject->transform.position;
	if (AEInputCheckTriggered(VK_RBUTTON))
	{
		AEVec2 mousePos = GetMouseWorldPos();
		targetPos = mousePos;
	}

	if (AEVec2Distance(&targetPos, currentPos) > Constants::PLAYER_SPEED * dt)
	{
		AEVec2Sub(&velocity, &targetPos, currentPos);
		AEVec2Normalize(&velocity, &velocity);
		AEVec2Scale(&velocity, &velocity, Constants::PLAYER_SPEED * dt);
		AEVec2Add(currentPos, currentPos, &velocity);
	}

}
