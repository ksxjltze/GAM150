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
	void PathFinderTest()
	{
		//set occupied nodes
		if (AEInputCheckTriggered(VK_RBUTTON))
		{
			A_Node* n = PathFinder::GetWorldGrid().GetNodeFromPosition(GetMouseWorldPos());
			n->occupied = true;
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
		
	
	
	}
	//draw can cause lag with alot of nodes
	void TestGrid()
	{
		PathFinder::GridDraw();
	}
}