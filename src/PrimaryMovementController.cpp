#include "PrimaryMovementController.h"
#include "constants.h"

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
	using namespace KEYBIND;
	float speed = 50.0f;
	float h = 0.0f, v = 0.0f;

	if (AEInputCheckCurr(MOVEMENT_UP))
		v = 1;
	
	if (AEInputCheckCurr(MOVEMENT_DOWN))
		v = -1;

	if (AEInputCheckCurr(MOVEMENT_LEFT))
		h = -1;
	
	if (AEInputCheckCurr(MOVEMENT_RIGHT))
		h = 1;
	
	movement.x = h * speed;
	movement.y = v * speed;

	rb->AddVelocity(movement, 1.0f);
}
