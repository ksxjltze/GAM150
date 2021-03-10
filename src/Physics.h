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
			
	};


}