#pragma once
#include <vector>
#include "Collider.h"
#include "ColliderAABB.h"

namespace TempTeam
{
	class CollisionManager
	{
	public:
		void Init();
		void AddCollider();
		void Update();
		void CheckCollision(ColliderAABB* collider1, ColliderAABB* collider2);
	private:
		std::vector<Collider*> colliderList;
		std::vector<ColliderAABB*> AABBColliderList;
	};
}