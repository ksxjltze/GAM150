#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
#include "ComponentCRTP.h"
namespace StarBangBang
{
	class RigidBody : public Component<RigidBody>
	{
	private:
		AEVec2 acceleration;
	
	public:
		//mass = 0 = infinity
		float mass ;
		float drag;
		AEVec2 velocity;
		

		float inv_mass() const;
		
		AEVec2 GetNormalizedVelocity() const
		{
			f32 mag = velocity.x * velocity.x + velocity.y * velocity.y;
			mag = sqrt(mag);
			return AEVec2{ velocity.x / mag, velocity.y / mag };
		}

		void Update();

		RigidBody(GameObject* gameObject);

		void AddForce(AEVec2 force, float scale);

		void AddVelocity(AEVec2 force, float scale);
			
	};


}