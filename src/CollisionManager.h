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
		
		void AddToColliders(BoxCollider);
		void ResolverUpdate();
		void AddToResolveQueue(CollisionPair);

		bool StaticAABB_Check(const BoxCollider& A, const BoxCollider& B, CollisionData& data);
		bool Dynamic_AABB(const BoxCollider& A, const AEVec2& vel1, const BoxCollider& B, const AEVec2& vel2, CollisionData& data);
		bool CircleVsCircle(CircleCollider c1, CircleCollider c2, CollisionData& col);

		void RecalculateColliderCells(BoxCollider&);

		void DebugCollider(BoxCollider b, Color c );

		void DebugCollider(CircleCollider c);


		BoxCollider* CreateBoxColliderInstance(GameObject* gameObject,bool is_static = true);

		bool ContainsPoint(const BoxCollider& box,AEVec2 pt);


		template<class T>
		void Resolve(T& obj1, T& obj2, const CollisionData& data)
		{
			if (obj1.isTrigger || obj2.isTrigger)
				return;
			//AEVec2 resolveForce;
			AEVec2 normal = data.col_normal;
			AEVec2 relVel = AEVec2{ obj2.rb->velocity.x - obj1.rb->velocity.x 
									,obj2.rb->velocity.y - obj1.rb->velocity.y };
			
			float dotVelScale = AEVec2DotProduct(&relVel, &normal);

			if (dotVelScale > 0)
				return;

			float scale = -(1 + bounciness) * dotVelScale ;
			float total = obj1.rb->inv_mass() + obj2.rb->inv_mass();

			if (total <= 0)
				return;

			// Apply impulse
			AEVec2 impulse{ normal.x * scale  , normal.y * scale };
		
			obj1.rb->AddVelocity(impulse, -obj1.rb->mass / total);
			obj2.rb->AddVelocity(impulse, obj2.rb->mass / total);
			
		
		}

	}
	
}

