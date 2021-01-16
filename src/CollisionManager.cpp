#include "CollisionManager.h"
#include <iostream>

void TempTeam::CollisionManager::Init()
{

}

void TempTeam::CollisionManager::AddCollider()
{

}

void TempTeam::CollisionManager::Update()
{
	for (ColliderAABB* collider1 : AABBColliderList)
	{
		for (ColliderAABB* collider2 : AABBColliderList)
		{
			CheckCollision(collider1, collider2);
		}
	}
}

void TempTeam::CollisionManager::CheckCollision(ColliderAABB* collider1, ColliderAABB* collider2)
{
	std::cout << "COLLISION" << std::endl;
}
