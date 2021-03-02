#pragma once
#include "CollisionManager.h"
#include "Utils.h"
#include "PathFinder.h"
#include <iostream>
namespace StarBangBang
{
	

	void FreeTest()
	{
		StarBangBang::FreeUnitMeshes();
		//PathFinder::Free();
	}
	bool start = false;
	
	AEVec2 startPos {-128,752};
	AEVec2 endPos{-514,840};
	std::vector<A_Node*> path;
	void PathFinderTest()
	{
		//set occupied nodes
		if (AEInputCheckTriggered(VK_RBUTTON))
		{
			A_Node* n = PathFinder::GetWorldGrid().GetNodeFromPosition(GetMouseWorldPos());
			if (n)
				n->occupied = true;
		}
			
		//set end pos and start pathfinding
		if (AEInputCheckTriggered(VK_LBUTTON))
		{
			endPos = GetMouseWorldPos();
			path = PathFinder::SearchForPath(startPos, endPos);
		}
		//place static collider (they cannot move)
		if (AEInputCheckTriggered(AEVK_Q))
		{
			BoxCollider b = BoxCollider(GetMouseWorldPos(), true ,120.0f, 120.0f);
		
		}
		//place dynamic collider
		if (AEInputCheckTriggered(AEVK_E))
		{
			BoxCollider b = BoxCollider(GetMouseWorldPos(), false, 120.0f, 120.0f);
		}
		if (AEInputCheckTriggered(AEVK_1))
			PRINT("(%f,%f)\n", GetMouseWorldPos().x, GetMouseWorldPos().y);
		
		if (path.empty())
			return;

		for (const A_Node* n : path)
		{
			DrawCircle(10.0f, n->nodePos);
		}
	
	}
	//draw can cause lag with alot of nodes
	void TestGrid()
	{
		PathFinder::GridDraw();
	}
}