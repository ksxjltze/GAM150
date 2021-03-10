#include "Physics.h"
using namespace StarBangBang;

RigidBody::RigidBody(GameObject* gameObject) :Component(gameObject), acceleration{ AEVec2{ 0,0 } },
mass{ 1.0f }, drag{0.1f},
velocity{ AEVec2{ 0,0 } } 
{}


float RigidBody::inv_mass() const
{
	return 1.0f / mass;
}

void StarBangBang::RigidBody::Update()
{
	f32 dt = static_cast<f32>(AEFrameRateControllerGetFrameTime());
	velocity.x += acceleration.x  * dt;
	velocity.y += acceleration.y  * dt;

	f32 mag = velocity.x * velocity.x + velocity.y * velocity.y;
	mag = (f32)sqrt(mag);

	if (mag != 0)
	{
		float k1 = 0.01f, k2 = 0.02f;
		float dragCo = mag * k1 + k2 * mag * mag;
		AEVec2 nVel = GetNormalizedVelocity();
		nVel.x *= -dragCo;
		nVel.y *= -dragCo;
		velocity.x += nVel.x;
		velocity.y += nVel.y;

	}
	//velocity.x *= 1.0f - drag;
	//velocity.y *= 1.0f - drag;
	gameObject->transform.position.x += velocity.x * dt;
	gameObject->transform.position.y += velocity.y  * dt;
	//PRINT("V:(%0.4f,%0.4f)\n", velocity.x, velocity.y);
}


void RigidBody::AddForce(AEVec2 force, float scale)
{
	//treat as infinity mass does not move
	if (mass <= 0)
	{
		return;
	}

	acceleration = AEVec2{ force.x / mass * scale,force.y /mass * scale};
	

}
void RigidBody::AddVelocity(AEVec2 force, float scale)
{
	force.x = force.x * scale;
	force.y = force.y * scale;
	velocity.x += force.x;
	velocity.y += force.y;

}

