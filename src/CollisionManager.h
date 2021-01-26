#pragma once
#include <vector>
#include "Collider.h"

namespace StarBangBang
{
	const float bounciness= 0.2f;
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
			
		public :
			
			
			bool CircleVsCircle(CircleCollider c1, CircleCollider c2, CollisionData& col);

			bool AABBvsAABB(BoxCollider b1, BoxCollider b2, CollisionData& col);

			void DebugCollider(BoxCollider b);

			void DebugCollider(CircleCollider c);
			
			//bool SATBox(BoxCollider b1, BoxCollider b2);
	
			template<class T>
			void Resolve(T& obj1, T& obj2, CollisionData* const data)
			{
				if (obj1.isTrigger || obj2.isTrigger)
					return;

				if (data)
				{
					AEVec2 resolveForce;
					if (data)
					{
						float scale = (1.0f + bounciness) + data->pen_depth ;
						AEVec2Scale(&resolveForce, &data->col_normal, scale);
						//movement force
						AEVec2 temp = obj1.center;
						AEVec2 temp1 = obj2.center;
						//push obj1
						if(!obj1.isStatic)
							AEVec2Add(&obj1.center, &temp, &resolveForce);
						//invert direction
						resolveForce = AEVec2{ resolveForce.x * -1.0f,resolveForce.y * -1.0f };
						//push obj2
						if(!obj2.isStatic)
							AEVec2Add(&obj2.center, &temp1, &resolveForce);
					}

				}
			}
			

		
			

	};
}