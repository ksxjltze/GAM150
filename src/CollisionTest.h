#pragma once
#include "CollisionManager.h"
#include "BasicMeshShape.h"
#include <iostream>
#include "Utils.h"
#include "Grid.h"
namespace StarBangBang
{
	CircleCollider circle1
		= CircleCollider(nullptr, AEVec2{ 0.0f,0.0f }, 200.0f);
	CircleCollider circle2
		= CircleCollider(nullptr, AEVec2{ 0.0f,0.0f }, 100.0f);
	BoxCollider box1
		= BoxCollider(nullptr, AEVec2{ 0.0f,100.0f }, 100.0f, 150.0f);
	BoxCollider box2
		= BoxCollider(nullptr, AEVec2{ 0.0f,200.0f }, 80.0f, 200.0f );

	CollisionManager manager = CollisionManager();
	CollisionData data = CollisionData();

	
	Grid grid;
	
	void InitTest()
	{
		
		grid.CreateGrid(30.0f, AEVec2{ static_cast<f32>(AEGetWindowWidth()), static_cast<f32>(AEGetWindowHeight()) });
	}

	void Test_BoxUpdate()
	{
		box1.isStatic = true;
		manager.DebugCollider(box1);
		manager.DebugCollider(box2);
		
		if (manager.AABBvsAABB(box1, box2, data))
		{
			//std::cout << "Box collide \n";
			manager.Resolve(box1, box2, &data);
		}
		if (AEInputCheckTriggered(VK_LBUTTON))
		{
			AEVec2 mousePos = GetMouseWorldPos();
			box2.center.x = mousePos.x;
			box2.center.y = mousePos.y;
		}
		
		//std::cout << "box2:(" << box2.center.x << "," << box2.center.y << ")\n";
		//std::cout << "box1:(" << box1.center.x << "," << box1.center.y << ")\n";

		
	}
	void Test_CircleUpdate()
	{	
		manager.DebugCollider(circle2);
		manager.DebugCollider(circle1);
	

		if (manager.CircleVsCircle(circle1, circle2, data))
		{
			//std::cout << "Circle collide \n";
			manager.Resolve(circle1,circle2,&data);
		}
		if (AEInputCheckTriggered(VK_LBUTTON))
		{
		
			AEVec2 mousePos = GetMouseWorldPos();

			circle2.center.x = mousePos.x;
			circle2.center.y = mousePos.y;
		
		}
		
	}
	
	void GridDrawTest()
	{
		AEVec2 mousePos = GetMouseWorldPos();
		Node* n = grid.GetNodeFromPosition(mousePos);
		if(n)
			StarBangBang::DrawCircle(10.0f,n->nodePos );
		grid.DrawGrid();
	}
}