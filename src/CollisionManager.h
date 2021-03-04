#pragma once
#include "Collider.h"
#include <queue>
namespace StarBangBang
{
	
	class Color;

	const float bounciness = 0.1f;
	
	class PartitionGrid;


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
		
		BoxCollider& A ;
		BoxCollider& B;
		CollisionData data;
		CollisionPair(BoxCollider& A, BoxCollider& B, CollisionData data);
	};



	namespace CollisionManager
	{
	
		void AddToColliders(BoxCollider);
		void ResolverUpdate();
		void AddToResolveQueue(CollisionPair);

		bool StaticAABB_Check(const BoxCollider& A, const BoxCollider& B, CollisionData& data);
		bool Dynamic_AABB(const BoxCollider& A, const AEVec2& vel1, const BoxCollider& B, const AEVec2& vel2, CollisionData& data);
		bool CircleVsCircle(CircleCollider c1, CircleCollider c2, CollisionData& col);

		void RecalculateColliderCells(BoxCollider&);

		void DebugCollider(BoxCollider b, Color c );

		void DebugCollider(CircleCollider c);


		bool ContainsPoint(const BoxCollider& box,AEVec2 pt);


		template<class T>
		void Resolve(T& obj1, T& obj2, const CollisionData& data,f32 dt)
		{
			if (obj1.isTrigger || obj2.isTrigger)
				return;
			AEVec2 resolveForce;
			AEVec2 normal = data.col_normal;

			float scale = !obj1.isStatic && !obj2.isStatic ?
				(1.0f + bounciness) + data.pen_depth * 0.5f
				: (1.0f + bounciness) + data.pen_depth;

			//movement force
			AEVec2Scale(&resolveForce, &normal, scale);
			//push obj1
			if (!obj1.isStatic)
			{
				obj1.Translate(resolveForce.x, resolveForce.y);
			}					
			//invert direction
			resolveForce = AEVec2{ resolveForce.x * -1.0f,resolveForce.y * -1.0f };
			//push obj2
			if (!obj2.isStatic)
			{
				obj2.Translate(resolveForce.x, resolveForce.y);
				
			}
	

		}

	}
	
}