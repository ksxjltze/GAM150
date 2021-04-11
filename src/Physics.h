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
		RigidBody(GameObject* gameObject);

		/*!*************************************************************************
		****
			\brief
				Get the inverse mass of the the rigidbody
			\param none

			\return
				The inverse mass of the the rigidbody
		****************************************************************************
		***/
		float inv_mass() const;

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
		void SetMass(float m);

		/*!*************************************************************************
		****
			\brief
				Whether the body is treated as kinematic 
				(whether to apply forces on this body)
			\param none
				
			\return
				true if forces affects this body
				otherwise false
		****************************************************************************
		***/
		bool isKinematic() const { return mass > 0; }
	

		/*!*************************************************************************
		****
			\brief
				Get the normalized velocity of the rigidbody
			\param none

			\return
				The normalized velocity
		****************************************************************************
		***/
		AEVec2 GetNormalizedVelocity() const;

		

		/*!*************************************************************************
		****
			\brief
				Gets the magnitude of the body's velocity vector
			\param none

			\return
				the magnitude of the body's velocity vector
		****************************************************************************
		***/
		f32 MagVelocity() const
		{
			return (f32)sqrt( ((double)velocity.x * (double)velocity.x + (double)velocity.y * (double)velocity.y));
		}

		/*!*************************************************************************
		****
			\brief
				Gets the squared magnitude of the body's velocity vector
			\param none

			\return
				the squared magnitude of the body's velocity vector
		****************************************************************************
		***/		
		f32 SqrVelocity() const
		{
			return velocity.x * velocity.x + velocity.y * velocity.y;
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
		void Update();

		
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
		void AddForce(AEVec2 force, float scale);


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
		void AddVelocity(AEVec2 v, float scale);


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
		void AddInstantVelocity(AEVec2 impulse, float scale);
	};
	class Ray
	{

	public:

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
		Ray(AEVec2 start, AEVec2 end);


		/*!*************************************************************************
		****
			\brief
				Computes the outward normal of the the ray 
			\param none
		
			\return
				The outward normal of the the ray 
		****************************************************************************
		***/
		AEVec2 Outward_Normal() const { return AEVec2{ v.y, -v.x }; }


		/*!*************************************************************************
		****
			\brief
				Get the direction vector of the ray
			\param none

			\return
				The direction vector of the ray
		****************************************************************************
		***/
		AEVec2 GetDirection() const { return v; }

		//starting point of the line
		const AEVec2 start;
		//ending point of the line
		const AEVec2 end;

	private:
		
		//direction
		AEVec2 v;

	
	};
	

}