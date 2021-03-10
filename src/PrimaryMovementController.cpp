#include "PrimaryMovementController.h"
#include "Physics.h"

StarBangBang::RigidBody* rb;
AEVec2 movement = AEVec2{0,0};
StarBangBang::PrimaryMovementController::PrimaryMovementController(GameObject* gameObject) : Script(gameObject)
{

}

void StarBangBang::PrimaryMovementController::Start()
{
	PRINT("Called\n");
	rb = gameObject->GetComponent<RigidBody>();
	if (rb)
	{
		PRINT("rb\n");
	}
}

void StarBangBang::PrimaryMovementController::Update()
{
	float dt = static_cast<float>(AEFrameRateControllerGetFrameTime());
	float speed = 20;
	if (rb)
	{
		if (AEInputCheckCurr(AEVK_W))
		{
			movement.y = speed;
	
			//gameObject->transform.position.y += speed;
		}
		if (AEInputCheckCurr(AEVK_A))
		{
			movement.x = -speed;
			//gameObject->transform.position.x -= speed;
		}
		if (AEInputCheckCurr(AEVK_S))
		{
			movement.y = -speed;
			//gameObject->transform.position.y -= speed;
		}
		if (AEInputCheckCurr(AEVK_D))
		{
			movement.x = speed;
			//gameObject->transform.position.x += speed;
		}
		//movement.x = speed;
		rb->AddVelocity(movement, 1.0f);

	}
	else
	{
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
}
