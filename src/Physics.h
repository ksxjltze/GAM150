/******************************************************************************/
/*!
\title		Captain Stealth
\file		Physics.h
\author 	Ho Yi Guan
\par    	email: Yiguan.ho@digipen.edu
\date   	April 08, 2021
\brief
			Contains the declaration for Physics.cpp
			Contains basic physics function
			-Rigibody & Rays 

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/


#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
#include "ComponentCRTP.h"
namespace StarBangBang
{
	class RigidBody : public Component<RigidBody>
	{
	private:
		AEVec2 acceleration;
		float inverse_mass;
		//mass <= 0 (infinity mass)
		float mass;
	public:
		
		float drag;
		AEVec2 velocity;
		

		float inv_mass() const;
		bool isKinematic() const { return mass > 0; }

		void SetMass(float m);

		AEVec2 GetNormalizedVelocity() const;

		
		//get the magnitude of the velocity
		f32 MagVelocity() const
		{
			return (f32)sqrt( ((double)velocity.x * (double)velocity.x + (double)velocity.y * (double)velocity.y));
		}

		//get the squared magnitude of the velocity
		f32 SqrVelocity() const
		{
			return velocity.x * velocity.x + velocity.y * velocity.y;
		}

		void Update();

		RigidBody(GameObject* gameObject);

		void AddForce(AEVec2 force, float scale);

		void AddVelocity(AEVec2 v, float scale);
		
		void AddInstantVelocity(AEVec2 impulse, float scale);
	};
	class Ray
	{

	public:
		Ray(AEVec2 start, AEVec2 end);

		AEVec2 Outward_Normal() const { return AEVec2{ v.y, -v.x }; }

		AEVec2 GetDirection() const { return v; }

		AEVec2 start;
		AEVec2 end;

	private:
		
		//direction
		AEVec2 v;

	
	};
	

}