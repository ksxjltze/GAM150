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
	float speed = 40.0f  ;
	float h = 0.0f, v = 0.0f;

	if (AEInputCheckCurr(AEVK_W))
		v = 1;
	
	if (AEInputCheckCurr(AEVK_S))
		v = -1;

	if (AEInputCheckCurr(AEVK_A))
		h = -1;
	
	if (AEInputCheckCurr(AEVK_D))
		h = 1;
	
	movement.x = h * speed;
	movement.y = v * speed;
	rb->AddForce(movement, 1.0f);
	//rb->AddVelocity(movement, 1.0f);
}
