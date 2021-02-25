#pragma once
#include "CollisionManager.h"
#include <iostream>
namespace StarBangBang
{
	CircleCollider circle1
		= CircleCollider(&GameObject(), AEVec2{ 0.0f,0.0f }, 10.0f);
	CircleCollider circle2
		= CircleCollider(&GameObject(), AEVec2{ 0.0f,0.0f }, 25.0f);
	BoxCollider box1
		= BoxCollider(&GameObject(), AEVec2{ 0.0f,0.0f }, 100.0f, 250.0f);
	BoxCollider box2
		= BoxCollider(&GameObject(), AEVec2{ 0.0f,0.0f }, 200.0f, 80.0f);

	CollisionManager manager = CollisionManager();
	CollisionData data = CollisionData();

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