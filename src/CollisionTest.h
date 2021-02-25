#pragma once
#include "CollisionManager.h"
#include "BasicMeshShape.h"
#include <iostream>
#include "Utils.h"
#include "PathFinder.h"
namespace StarBangBang
{
	static CircleCollider circle1
		= CircleCollider( AEVec2{ 0.0f,0.0f }, 200.0f);
	static CircleCollider circle2
		= CircleCollider( AEVec2{ 0.0f,0.0f }, 100.0f);
	static BoxCollider box1
		= BoxCollider( AEVec2{ 0.0f,100.0f }, 100.0f, 150.0f);
	static BoxCollider box2
		= BoxCollider( AEVec2{ 0.0f,200.0f }, 80.0f, 200.0f );

	static CollisionData data = CollisionData();

	void InitTest()
	{
		
	}

	void FreeTest()
	{
		StarBangBang::FreeUnitMeshes();
		PathFinder::Free();
	}
	bool start = false;
	void Test_BoxUpdate()
	{
		float dt = (float)AEFrameRateControllerGetFrameTime();
		//box1.isStatic = true;
		CollisionManager::DebugCollider(box1);
		CollisionManager::DebugCollider(box2);
		if (CollisionManager::Dynamic_AABB(box1, AEVec2{ -500,0 },box2, AEVec2{ 500,0 },data))
		{
			
			CollisionManager::Resolve(box1, box2, data);
		}
		if (AEInputCheckTriggered(VK_LBUTTON))
		{		
			start = !start;
		}
		if (start)
		{
			box2.center.x += -500 * dt;
			box1.center.x += 500 * dt;
		}
	
	}
	void Test_CircleUpdate()
	{	
		CollisionManager::DebugCollider(circle2);
		CollisionManager::DebugCollider(circle1);
	

		if (CollisionManager::CircleVsCircle(circle1, circle2, data))
		{
			//std::cout << "Circle collide \n";
			CollisionManager::Resolve(circle1,circle2,data);
		}
		if (AEInputCheckTriggered(VK_LBUTTON))
		{
		
			AEVec2 mousePos = GetMouseWorldPos();

			circle2.center.x = mousePos.x;
			circle2.center.y = mousePos.y;
		
		}
		
	}
	AEVec2 startPos {-128,752};
	AEVec2 endPos{-514,840};
	std::vector<Node*> path;
	void PathFinderTest()
	{
		//set start pos 
		if (AEInputCheckTriggered(VK_RBUTTON))
			startPos = GetMouseWorldPos();

		//set end pos and start pathfinding
		if (AEInputCheckTriggered(VK_LBUTTON))
		{
			endPos = GetMouseWorldPos();
			path = PathFinder::SearchForPath(startPos, endPos);
		}
		if (AEInputCheckTriggered(AEVK_RETURN))
		{
			PathFinder::worldGrid.GetNodeFromPosition(GetMouseWorldPos())->occupied = true;
		}
		if (AEInputCheckTriggered(AEVK_1))
			PRINT("(%f,%f)\n", GetMouseWorldPos().x, GetMouseWorldPos().y);
		
		if (path.empty())
			return;

		for (const Node* n : path)
		{
			DrawCircle(10.0f, n->nodePos);
		}

		
			

		

	
	}
	void TestGrid()
	{
		PathFinder::GridDraw();
	}
}