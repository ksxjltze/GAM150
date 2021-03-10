#include "Physics.h"
using namespace StarBangBang;

const float EPILISON = 0.00000001f;

RigidBody::RigidBody(GameObject* gameObject) :Component(gameObject), acceleration{ AEVec2{ 0,0 } }, 
inverse_mass{ 1.0f }, mass{1.0f}, drag{ 0.1f }, velocity{ AEVec2{ 0,0 } }
{

	
}


AEVec2 RigidBody::GetNormalizedVelocity() const
{
	f32 mag = velocity.x * velocity.x + velocity.y * velocity.y;
	mag = (f32)sqrt(mag);
	if (mag < EPILISON && mag > -EPILISON)
	{
		return AEVec2{ 0.0f,0.0f };
	}

	return AEVec2{ velocity.x / mag, velocity.y / mag };
}

float RigidBody::inv_mass() const
{
	return inverse_mass;
}

void RigidBody::SetMass(float m)
{
	mass = m;
	inverse_mass = 1.0f / m;
}

void StarBangBang::RigidBody::Update()
{
	f32 dt = static_cast<f32>(AEFrameRateControllerGetFrameTime());
	velocity.x += acceleration.x  * dt;
	velocity.y += acceleration.y  * dt;

	/*float realDrag = 0.5f * MagVelocity() +  drag * SqrVelocity();
	AEVec2 n = GetNormalizedVelocity();
	velocity.x += n.x * -realDrag;
	velocity.y += n.y * -realDrag;*/

	drag = AEClamp(drag,0.0f,1.0f);

	velocity.x *= 1.0f - drag;
	velocity.y *= 1.0f - drag;
	
	//PRINT("\nn:(%.3f,%.3f) \n", n.x, n.y);
	//PRINT("\nv:(%.3f,%.3f) \n", velocity.x, velocity.y);
	//if velocity is really small reset
	if (SqrVelocity() < EPILISON && SqrVelocity() > -EPILISON)
	{
		velocity.x = 0;
		velocity.y = 0;
	}

	
	
	gameObject->transform.position.x += velocity.x ;
	gameObject->transform.position.y += velocity.y ;

	//PRINT("V:(%0.4f,%0.4f)\n", velocity.x, velocity.y);
}

//add acceleration via force
void RigidBody::AddForce(AEVec2 force, float scale)
{
	//treat as infinity mass does not move
	if (mass <= 0.0f)
		return;


	acceleration = AEVec2{ force.x * inverse_mass * scale,force.y * inverse_mass * scale};
	

}
//add instant velocity via impulse
void RigidBody::AddVelocity(AEVec2 impulse, float scale)
{
	impulse.x *=  scale;
	impulse.y *=  scale;
	
	velocity.x += impulse.x;
	velocity.y += impulse.y;

}

