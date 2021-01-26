#include "PrimaryMovementController.h"

StarBangBang::PrimaryMovementController::PrimaryMovementController(GameObject* gameObject) : Script(gameObject)
{
	doodoo = 5;
}

void StarBangBang::PrimaryMovementController::Start()
{

}

void StarBangBang::PrimaryMovementController::Update()
{
	float dt = (float)AEFrameRateControllerGetFrameTime();
	float speed = Constants::PLAYER_SPEED * dt;
	if (AEInputCheckCurr(AEVK_W))
	{
		gameObject->transform.position.y += speed;
	}
	if (AEInputCheckCurr(AEVK_A))
	{
		gameObject->transform.position.x -= speed;
	}
	if (AEInputCheckCurr(AEVK_S))
	{
		gameObject->transform.position.y -= speed;
	}
	if (AEInputCheckCurr(AEVK_D))
	{
		gameObject->transform.position.x += speed;
	}
}
