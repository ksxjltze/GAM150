#pragma once
#include <vector>
#include "Collider.h"

namespace StarBangBang
{
	struct CollisionData
	{
		Collider* obj_1;
		Collider* obj_2;
		float pen_depth;
		AEVec2 col_normal;
	};

	class CollisionManager
	{
		private:
			AEVec2 ProjectOnToAxis(AEVec2 v, AEVec2 axis);
		
			
		public :
			bool CircleVsCircle(CircleCollider c1, CircleCollider c2, CollisionData* collision);
			bool AABBvsAABB(BoxCollider b1, BoxCollider b2);
			
			void Resolve_CirclevsCircle(CircleCollider c1, CircleCollider c2, CollisionData col);

			void DebugCollider(BoxCollider c);

			void DebugCollider(CircleCollider c);
			
			void Resolve_BoxvsBox(BoxCollider b1, BoxCollider b2, CollisionData col);
			//bool SATBox(BoxCollider b1, BoxCollider b2);
		
			

	};
}