#include "Physics.h"
using namespace StarBangBang;

const float drag = 1.0f;
const AEVec2 resistance = AEVec2{ 1,1 };


RigidBody::RigidBody(float _mass, AEVec2 _velocity , AEVec2 _acceleration, AEVec2 _position ) :
	mass{ _mass }, inv_mass{ 1 / _mass }, velocity{ _velocity }, acceleration{ _acceleration }, position{ _position }
	{};

void RigidBody::RB_AddForce(AEVec2 force, float scale)
{
	//treat as infinity mass does not move
	if (mass == 0)
	{
		return;
	}

	acceleration = AEVec2{ force.x / mass * scale,force.y /mass * scale};
	

}
void RigidBody::RB_AddVelocity(AEVec2 force, float scale)
{
	force.x = force.x * scale;
	force.y = force.y * scale;
	velocity.x += force.x;
	velocity.y += force.y;

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
