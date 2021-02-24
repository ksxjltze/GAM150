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
		StarBangBang::InitBasicMesh();
		PathFinder::Init();
		//grid.CreateGrid(30.0f, AEVec2{ static_cast<f32>(AEGetWindowWidth()), static_cast<f32>(AEGetWindowHeight()) });
	}

	void FreeTest()
	{
		StarBangBang::FreeUnitMeshes();
		PathFinder::Free();
	}
	bool start = false;
	void Test_BoxUpdate()
	{
		float dt = AEFrameRateControllerGetFrameTime();
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
	AEVec2 endPos{-415,389};
	
	void PathFinderTest()
	{
		if (AEInputCheckTriggered(VK_LBUTTON))
		{
			endPos = GetMouseWorldPos();
		}
		//set occupied node for testing
		if (AEInputCheckTriggered(VK_RBUTTON))
		{
			Node* n = PathFinder::grid.GetNodeFromPosition(GetMouseWorldPos());
			if (n)
			{
				n->occupied = true;
			}
				
		}

		for (int y = 0; y < PathFinder::grid.GetGridSizeY(); y++)
		{
			for (int x = 0; x < PathFinder::grid.GetGridSizeX(); x++)
			{
				if (PathFinder::grid.GetNode(y, x)->occupied)
				{
					std::cout << "Set\n";
				}
			}
		}
		//std::cout << '(' << GetMouseWorldPos().x << ',' << GetMouseWorldPos().y << ")\n";
		PathFinder::SearchForPath(startPos, endPos);

	
	}
	void TestGrid()
	{
		PathFinder::GridDraw();
	}
}