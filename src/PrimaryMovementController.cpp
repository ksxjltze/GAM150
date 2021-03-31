#include "PrimaryMovementController.h"
#include "PlayerScript.h"

AEVec2 movement = AEVec2{0,0};
StarBangBang::PrimaryMovementController::PrimaryMovementController(GameObject* gameObject) : Script(gameObject), rb{nullptr}
{

}

void StarBangBang::PrimaryMovementController::Start()
{
	rb = gameObject->GetComponent<RigidBody>();
	rb->drag = 0.2f;
}

void StarBangBang::PrimaryMovementController::Update()
{
	// Don't allow player to move when detected
	PlayerScript* playerScript = gameObject->GetComponent<PlayerScript>();
	if (playerScript)
	{
		if (playerScript->GetDetected())
			return;
	}

	float speed = 50.0f;
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

	rb->AddVelocity(movement, 1.0f);
}
