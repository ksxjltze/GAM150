/******************************************************************************/
/*!
\title		Captain Stealth
\file		Physics.cpp
\author 	Ho Yi Guan
\par    	email: Yiguan.ho@digipen.edu
\date   	April 08, 2021
\brief
			Contains the definition for Physics.h
			Contains basic physics function
			-Rigibody & Rays

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/


#include "Physics.h"
#include "globals.h"
using namespace StarBangBang;

const float EPILISON = 0.000001f;


/*!*************************************************************************
****
	\brief
		Rigidbody constructor
	\param gameObject
		The gameObject* to init the component
	\return
		void
****************************************************************************
***/

RigidBody::RigidBody(GameObject* gameObject) :Component(gameObject), acceleration{ AEVec2{ 0,0 } }, 
inverse_mass{ 1.0f }, mass{1.0f}, drag{ 0.1f }, velocity{ AEVec2{ 0,0 } }
{

	
}

/*!*************************************************************************
****
	\brief
		Get the normalized velocity of the rigidbody
	\param none
		
	\return
		The normalized velocity
****************************************************************************
***/

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

/*!*************************************************************************
****
	\brief
		Get the inverse mass of the the rigidbody
	\param none

	\return
		The inverse mass of the the rigidbody
****************************************************************************
***/

float RigidBody::inv_mass() const
{
	return inverse_mass;
}

/*!*************************************************************************
****
	\brief
		Sets the mass of the the rigidbody
	\param m
		The new mass of the rigidybody
	\return
		void
****************************************************************************
***/

void RigidBody::SetMass(float m)
{
	mass = m;
	if(m <= 0)
	{
		inverse_mass = 0.0f;
		return;
	}
	inverse_mass = 1.0f / m;
}


/*!*************************************************************************
****
	\brief
		Rigidbody update function
	\param none
		
	\return
		void
****************************************************************************
***/
void StarBangBang::RigidBody::Update()
{
	velocity.x += acceleration.x * g_dt;
	velocity.y += acceleration.y  * g_dt;

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
	if (SqrVelocity() < EPILISON )
	{
		velocity.x = 0;
		velocity.y = 0;
	}
	
	gameObject->transform.position.x += velocity.x * g_dt;
	gameObject->transform.position.y += velocity.y * g_dt;

	//PRINT("V:(%0.4f,%0.4f)\n", velocity.x, velocity.y);
}

/*!*************************************************************************
****
	\brief
		Add a force via acceleration
	\param force
		The force to add
	\param scale
		A scale to apply to the param force
	\return
		void
****************************************************************************
***/
void RigidBody::AddForce(AEVec2 force, float scale)
{
	//treat as infinity mass does not move
	if (mass <= 0.0f)
		return;

	acceleration = AEVec2{ force.x * inverse_mass * scale,force.y * inverse_mass * scale};	

}

/*!*************************************************************************
****
	\brief
		Add an instant velocity to change position
	\param impulse
		The change in velocity over time
	\param scale
		A scale to apply to the param impulse
	\return
		void
****************************************************************************
***/
void RigidBody::AddInstantVelocity(AEVec2 impulse, float scale)
{
	impulse.x *= scale;
	impulse.y *= scale; 
	gameObject->transform.position.x += impulse.x;

	gameObject->transform.position.y += impulse.y;

}


/*!*************************************************************************
****
	\brief
		Add param v to velocity 
	\param v
		The velocity to add
	\param scale
		A scale to apply to the param impulse
	\return
		void
****************************************************************************
***/
void RigidBody::AddVelocity(AEVec2 v, float scale)
{
	if (mass <= 0)
		return;

	v.x *=  scale;
	v.y *=  scale;
	
	velocity.x += v.x;
	velocity.y += v.y;

}


/*!*************************************************************************
****
	\brief
		Constructs a ray
	\param start
		The starting point of the ray
	\param end
		The ending point of the ray
	\return
		void
****************************************************************************
***/
StarBangBang::Ray::Ray(AEVec2 start, AEVec2 end) : start{ start }, end{ end }, v{ AEVec2{end.x - start.x, end.y - start.y} }
{

}

