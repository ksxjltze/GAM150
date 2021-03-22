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

		

		f32 MagVelocity() const
		{
			return (f32)sqrt( ((double)velocity.x * (double)velocity.x + (double)velocity.y * (double)velocity.y));
		}

		f32 SqrVelocity() const
		{
			return velocity.x * velocity.x + velocity.y * velocity.y;
		}

		void Update();

		RigidBody(GameObject* gameObject);

		void AddForce(AEVec2 force, float scale);

		void AddVelocity(AEVec2 force, float scale);
		
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