#pragma once
#include "Collider.h"
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
		bool operator<(const CollisionPair& rhs) const
		{
			return A.Max().x < rhs.A.Max().x;
		}
	
	};



	namespace CollisionManager
	{
		void Free();
		void AddToColliders(BoxCollider);
		void ResolverUpdate();
		void AddToResolveQueue(CollisionPair);

		bool StaticAABB_Check(const BoxCollider& A, const BoxCollider& B);
		bool Dynamic_AABB(const BoxCollider& A, const AEVec2& vel1, const BoxCollider& B, const AEVec2& vel2);
		bool CircleVsCircle(CircleCollider c1, CircleCollider c2, CollisionData& col);

		void RecalculateColliderCells(BoxCollider&);

		void DebugCollider(BoxCollider b, Color c );

		void DebugCollider(CircleCollider c);

		void ClearPartitionGridCell(int index);

		void ClearPartitionGridCells();

		void RemoveCollider(Collider* pCollider);


		BoxCollider* CreateBoxColliderInstance(GameObject* gameObject,bool is_static = true);

		bool ContainsPoint(const BoxCollider& box,AEVec2 pt);


		

	}
	
}

