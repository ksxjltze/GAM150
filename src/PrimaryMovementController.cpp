#include "PrimaryMovementController.h"
#include "Physics.h"

StarBangBang::RigidBody* rb;
AEVec2 movement = AEVec2{0,0};
StarBangBang::PrimaryMovementController::PrimaryMovementController(GameObject* gameObject) : Script(gameObject)
{

}

void StarBangBang::PrimaryMovementController::Start()
{
	rb = gameObject->GetComponent<RigidBody>();
	rb->drag = 0.2f;
}

void StarBangBang::PrimaryMovementController::Update()
{
	float dt = static_cast<float>(AEFrameRateControllerGetFrameTime());
	float speed = 40 * dt ;
	if (AEInputCheckCurr(AEVK_W))
	{
		movement.y = speed;

	}
	
	if (AEInputCheckCurr(AEVK_A))
	{
		movement.x = -speed;

	}
	
	if (AEInputCheckCurr(AEVK_S))
	{
		movement.y = -speed;

	}
	
	if (AEInputCheckCurr(AEVK_D))
	{
		movement.x = speed;

	}
	

	rb->AddVelocity(movement, 1.0f);
}
