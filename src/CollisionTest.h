#pragma once
#include "CollisionManager.h"
#include "BasicMeshShape.h"
#include <iostream>
namespace StarBangBang
{

	

	CircleCollider circle1
		= CircleCollider(nullptr, AEVec2{ 0.0f,0.0f }, 200.0f);
	CircleCollider circle2
		= CircleCollider(nullptr, AEVec2{ 0.0f,0.0f }, 100.0f);
	BoxCollider box1
		= BoxCollider(nullptr, AEVec2{ 0.0f,200.0f }, 200.0f, 200.0f);
	BoxCollider box2
		= BoxCollider(nullptr, AEVec2{ 0.0f,200.0f }, 200.0f, 200.0f);

	CollisionManager manager = CollisionManager();
	CollisionData data = CollisionData();
	s32 x = 0, y = 0;

	bool update_Box = false;

	void Test_BoxUpdate()
	{

		manager.DebugCollider(box1);
		manager.DebugCollider(box2);
		
		if (manager.AABBvsAABB(box1, box2, data))
		{
			std::cout << "Collided \n";
			manager.Resolve_BoxvsBox(box1, box2, &data);
		}
		if (AEInputCheckTriggered(VK_LBUTTON))
		{
			update_Box = !update_Box;
		}
		if (update_Box)
		{
			AEInputGetCursorPosition(&x, &y);
			box2.center.x = static_cast<f32>(x);
			box2.center.y = static_cast<f32>(-y);
			//std::cout << "Move \n";
		}
		//std::cout << "box2:(" << box2.center.x << "," << box2.center.y << ")\n";
		//std::cout << "box1:(" << box1.center.x << "," << box1.center.y << ")\n";

		
	}
	bool update_circle = false;
	void Test_CircleUpdate()
	{	
		manager.DebugCollider(circle2);
		manager.DebugCollider(circle1);
	

		if (manager.CircleVsCircle(circle1, circle2, data))
		{
			manager.Resolve_CirclevsCircle(circle1,circle2,&data);
		}
		if (AEInputCheckTriggered(VK_LBUTTON))
		{
		
			update_circle = !update_circle;
			
		
		}
		if (update_circle)
		{
			AEInputGetCursorPosition(&x, &y);
			circle2.center.x = static_cast<f32>(x);
			circle2.center.y = static_cast<f32>(-y);
		}
	}
}