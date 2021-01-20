#include "SecondaryMovementController.h"
#include "Utils.h"
#include <iostream>

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

		std::cout << "World: " << mousePos.x << " " << mousePos.y << std::endl;
		std::cout << "GameObject: " << gameObjectPos->x << " " << gameObjectPos->y << std::endl;

		AEVec2Sub(&velocity, &mousePos, gameObjectPos);
		AEVec2Normalize(&velocity, &velocity);
	}
	AEVec2Add(&gameObject->transform.position, &gameObject->transform.position, &velocity);

}
