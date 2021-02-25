#pragma once
#include "CollisionManager.h"
#include "BasicMeshShape.h"
#include <iostream>
#include "Utils.h"
#include "PathFinder.h"
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

		
	void Test_BoxUpdate()
	{
		manager.DebugCollider(box1);
		manager.DebugCollider(box2);


		if (manager.AABBvsAABB(box1, box2, &data))
		{
			manager.Resolve_BoxvsBox(box1, box2, &data);
		}
		if (AEInputCheckTriggered(VK_LBUTTON))
		{
			int x = 0, y = 0;
			AEInputGetCursorPosition(&x, &y);
			box2.center.x = (f32)x;
			box2.center.y = (f32)y;

		}
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
	
	void TestGrid()
	{
		PathFinder::GridDraw();
		if (manager.CircleVsCircle(circle1, circle2, &data))
		{
			manager.Resolve_CirclevsCircle(circle1,circle2,&data);
		}
		if (AEInputCheckTriggered(VK_LBUTTON))
		{
			int x = 0, y = 0;
			AEInputGetCursorPosition(&x,&y);
			circle2.center.x = (f32)x;
			circle2.center.y = (f32)y;

		}
	}
}