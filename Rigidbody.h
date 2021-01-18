#pragma once
#include "Src/Transform.h"
//#include "Extern/AlphaEngine_V3.08/include/AEVec2.h"

namespace StarBangBang 
{
	struct Rigidbody
	{
		public:
			AEVec2 position;
			float inv_mass;
			float mass;
			AEVec2 velocity = {0,0};
			AEVec2 force = { 0,0 };
			float gravityScale;

			Rigidbody(AEVec2 _position, float _mass, float _gravityScale);

	};


}