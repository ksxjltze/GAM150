#pragma once
#include <vector>
#include "Collider.h"

namespace StarBangBang
{
	struct CollisionData
	{
		public:
			float pen_depth = 0.0f;
			AEVec2 col_normal;
			
			CollisionData() 
			{
				col_normal = AEVec2{ 0.0f,0.0f };
				
			}
			~CollisionData() {}
	};

	class CollisionManager
	{
		private:
			AEVec2 ProjectOnToAxis(AEVec2 v, AEVec2 axis);
		
			
		public :
			
			bool CircleVsCircle(CircleCollider c1, CircleCollider c2, CollisionData& col);

			bool AABBvsAABB(BoxCollider b1, BoxCollider b2, CollisionData& col);

			void Resolve_CirclevsCircle(CircleCollider c1, CircleCollider c2, CollisionData* const col);

			void Resolve_BoxvsBox(BoxCollider& b1, BoxCollider& b2, CollisionData* const col);

			void DebugCollider(BoxCollider b);

			void DebugCollider(CircleCollider c);
			
			//bool SATBox(BoxCollider b1, BoxCollider b2);
		
			

	};
}