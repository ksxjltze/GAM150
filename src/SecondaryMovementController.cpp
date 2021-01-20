#include "SecondaryMovementController.h"
#include "Utils.h"

void StarBangBang::SecondaryMovementController::Start()
{

}

void StarBangBang::SecondaryMovementController::Update()
{
	if (AEInputCheckTriggered(VK_LBUTTON))
	{
		AEVec2* gameObjectPos = &gameObject->transform.position;
		AEVec2 mousePos = GetMouseWorldPos();
		double dt = AEFrameRateControllerGetFrameTime();

		AEVec2Sub(&velocity, &mousePos, gameObjectPos);
		AEVec2Normalize(&velocity, &velocity);
	}
	AEVec2Add(&gameObject->transform.position, &gameObject->transform.position, &velocity);

}
