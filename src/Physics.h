#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
namespace StarBangBang
{
	class RigidBody
	{
		public:
			//mass = 0 = infinity
			float mass;
			float inv_mass;
			AEVec2 velocity = AEVec2{0,0};
			AEVec2 acceleration = AEVec2{0,0};
			
			void RB_AddForce(AEVec2 force, float scale = 1.0f);
			void RB_Update(void);

			RigidBody(float _mass, AEVec2 _velocity = AEVec2{ 0,0 }, AEVec2 _acceleration = AEVec2{ 0,0 })
			{
				mass = _mass;
				inv_mass = 1 / _mass;
				velocity = _velocity;
				acceleration = _acceleration;
			}
			~RigidBody() {};
	};


	void Physics_Update(void);
}