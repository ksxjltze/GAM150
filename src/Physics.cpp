#include "Physics.h"
using namespace StarBangBang;

const float drag = 1.0f;
const AEVec2 resistance = AEVec2{ 1,1 };
void RigidBody::RB_AddForce(AEVec2 force, float scale)
{
	//treat as infinity mass does not move
	if (mass == 0)
	{
		return;
	}

	acceleration = AEVec2{ force.x / mass * scale,force.y /mass * scale};
	

}

void RigidBody::RB_Update(void)
{
	f32 dt = static_cast<f32>(AEFrameRateControllerGetFrameTime());
	velocity.x += (acceleration.x + resistance.x * -drag) * dt ;
	velocity.y += (acceleration.y + resistance.y * -drag) * dt;

	
}

void StarBangBang::Physics_Update(void)
{

}
