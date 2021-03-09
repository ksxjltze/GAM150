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
	void PathFinderTest()
	{
		//set occupied nodes
		if (AEInputCheckTriggered(VK_RBUTTON))
		{
			A_Node* n = PathFinder::GetWorldGrid().GetNodeFromPosition(GetMouseWorldPos());
			if (n)
				n->occupied = true;
		}
			
		//place static collider (they cannot move)
		if (AEInputCheckTriggered(AEVK_Q))
		{
			//BoxCollider b = BoxCollider(GetMouseWorldPos(), true , 50.0f, 50.0f);
		
		}
		//place dynamic collider
		if (AEInputCheckTriggered(AEVK_E))
		{
			//BoxCollider b = BoxCollider(GetMouseWorldPos(), false, 50.0f, 50.0f);
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