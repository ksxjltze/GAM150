#include "CollisionManager.h"
#include <iostream>

void StarBangBang::CollisionManager::Init()
{

}

void StarBangBang::CollisionManager::AddCollider()
{

}

void StarBangBang::CollisionManager::Update()
{
	for (ColliderAABB* collider1 : AABBColliderList)
	{
		for (ColliderAABB* collider2 : AABBColliderList)
		{
			CheckCollision(collider1, collider2);
		}
	}
}

void StarBangBang::CollisionManager::CheckCollision(ColliderAABB* collider1, ColliderAABB* collider2)
{
	std::cout << "COLLISION" << std::endl;
}
