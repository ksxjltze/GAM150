#pragma once
#include "Collider.h"
#include <queue>
namespace StarBangBang
{
	const float bounciness = 0.1f;

	struct CollisionData
	{
	public:
		float pen_depth = 0.0f;
		AEVec2 col_normal;

		CollisionData();

	};
	struct CollisionPair
	{
	public:
		CollisionData data = CollisionData();
		BoxCollider A;
		BoxCollider B;
		
		CollisionPair() = default;
	};



	namespace CollisionManager
	{
		void ResolverUpdate();
		void AddToResolveQueue(CollisionPair&);

		bool StaticAABB_Check(const BoxCollider& A, const BoxCollider& B, CollisionData& data);
		bool Dynamic_AABB(const BoxCollider& A, const AEVec2& vel1, const BoxCollider& B, const AEVec2& vel2, CollisionData& data);
		bool CircleVsCircle(CircleCollider c1, CircleCollider c2, CollisionData& col);

			
		void DebugCollider(BoxCollider b);

		void DebugCollider(CircleCollider c);

		template<class T>
		void Resolve(T& obj1, T& obj2, const CollisionData& data)
		{
			if (obj1.isTrigger || obj2.isTrigger)
				return;

			AEVec2 resolveForce;
			AEVec2 normal = data.col_normal;

			float scale = (1.0f + bounciness) + data.pen_depth;
			AEVec2Scale(&resolveForce, &normal, scale);
			//movement force
			AEVec2 temp = obj1.center;
			AEVec2 temp1 = obj2.center;
			//push obj1
			if (!obj1.isStatic)
				AEVec2Add(&obj1.center, &temp, &resolveForce);
			//invert direction
			resolveForce = AEVec2{ resolveForce.x * -1.0f,resolveForce.y * -1.0f };
			//push obj2
			if (!obj2.isStatic)
				AEVec2Add(&obj2.center, &temp1, &resolveForce);

			}

	}
	
}