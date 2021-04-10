/******************************************************************************/
/*!
\title		Captain Stealth
\file		PathFinder.cpp
\author 	Ho Yi Guan
\par    	email: Yiguan.ho@digipen.edu
\date   	April 08, 2021
\brief
			Contains the definition for PathFinder.h
			Contains functions for pathfinding and grid object

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/


#include "PathFinder.h"
#include <unordered_set>
#include <algorithm>
#include "Utils.h"
#include "BasicMeshShape.h"
#include <iostream>
#include "constants.h"
#include "Heap.hpp"
using namespace StarBangBang;

//diagonal movement cost
const int diagonal_Cost = 14;

//straight movement cost
const int straight_Cost = 10;

//grid visiblity flag
static bool isVisible = true;

//the world's grid object
Grid worldGrid;


//compare node functor for the heap
struct A_Node_Greater
{
	bool operator ()(const A_Node* lhs, const A_Node* rhs) const
	{
		if (lhs->GetfCost() > rhs->GetfCost())
			return true;
		if (rhs->GetfCost() > lhs->GetfCost())
			return false;
		if (lhs->hcost > rhs->hcost)
			return true;
		if (rhs->hcost > lhs->hcost)
			return false;

		return false;
	}
};

/*!*************************************************************************
****
	\brief
		Initialise the pathfinder grid to be used for the game world
	\param rows
		The number of rows of the matrix
	\param cols
		The number of columns of the matrix
	\return
		void

****************************************************************************
***/
void PathFinder::PathFinderInit()
{
	//worldGrid.CreateGrid(64,50,50, AEVec2{ 0,0 });

	//Fit to tilemap (Default)
	float size = TILEMAP::DEFAULT_TILE_SIZE;
	worldGrid.CreateGrid(size, 50, 50, AEVec2{ -size / 2, size /2 });
}

/*!*************************************************************************
****
	\brief
		Display the world grid
	\param visible
		Whether the grid should be drawn
	\return
		void

****************************************************************************
***/
void StarBangBang::PathFinder::ShowGrid(bool visible)
{
	isVisible = visible;
}

/*!*************************************************************************
****
	\brief
		Free the world grid
	\param visible
		Whether the grid should be drawn
	\return
		void
****************************************************************************
***/
void PathFinder::Free()
{
	worldGrid.FreeGrid();
}


/*!*************************************************************************
****
	\brief
		Draws the world grid
	\return
		void
****************************************************************************
***/
void PathFinder::GridDraw()
{
	if (isVisible)
	{
	
		worldGrid.DrawGrid();

	}
}

/*!*************************************************************************
****
	\brief
		Get a reference to the world grid data
	\return
		The world grid data reference
****************************************************************************
***/
Grid& PathFinder::GetWorldGrid()
{
	return worldGrid;
}


int NodeDistance(const A_Node* lhs, const A_Node* rhs)
{
	int distX = abs(lhs->index_x - rhs->index_x);
	int distY = abs(lhs->index_y - rhs->index_y);

	if (distX > distY)
	{
		return  distY * diagonal_Cost + (distX - distY) * straight_Cost;
	}
	
	return distX * diagonal_Cost + (distY - distX) * straight_Cost;

	
}


/*!*************************************************************************
****
	\brief
		Retrace the nodes to get the correct pathing
	\param start
		The starting node
	\param end
		The end node
	\param pathing
		The reference vector container to store the found path nodes
	\return
		void
****************************************************************************
***/
void TracePath(A_Node* start, A_Node* end , std::vector<A_Node*>& p)
{
	
	A_Node* currNode = end;

	//we reach our last node (stop)
	while (currNode != start)
	{
		currNode->occupied = true;
		p.push_back(currNode);
		//trace back to prev node using its parent
		currNode = currNode->parent;
	}
	p.push_back(start); 
	std::reverse(p.begin(), p.end());

	////simpify path to contain turning points
	//for (int i = 1 ; i < temp.size() ; ++i)
	//{
	//	newDir.x = temp[i]->index_x;
	//	newDir.y = temp[i]->index_y;

	//	if (newDir.x != prevDir.x && newDir.y != prevDir.y)
	//	{
	//		p.push_back(temp[i]->nodePos);
	//	}

	//	prevDir = newDir;
	//}

}

/*!*************************************************************************
****
	\brief
		Search for a path given a start and end position
	\param start
		The starting positions
	\param target
		The target position to reach
	\param pathing
		The reference vector container to store the found path nodes
	\return
		void
****************************************************************************
***/
void PathFinder::SearchForPath(AEVec2 start, AEVec2 target, std::vector<A_Node*>& pathing)
{
	pathing.reserve(50);

	A_Node* startNode = worldGrid.GetNodeFromPosition(start);
	A_Node* endNode = worldGrid.GetNodeFromPosition(target);
	Heap<A_Node*, std::vector<A_Node*>, A_Node_Greater> openList;

	std::unordered_set<A_Node*> closeList;
	closeList.reserve(50);

	//invalid positions
	if (!endNode || !startNode)
		return;
	if (endNode->occupied)
	{
		//PRINT("End node occupied\n");
		return;
	}

	openList.push(startNode);

	while (openList.size() > 0)
	{
		A_Node* currNode = openList.top();
		openList.pop();
		//scanned nodes
		closeList.insert(currNode);

		if (currNode == endNode)
		{
			TracePath(startNode, endNode, pathing);
			return;
		}


		for (A_Node* neighbour : worldGrid.Get4_NodeNeighbours(currNode))
		{
			std::unordered_set<A_Node*>::const_iterator u_iter = closeList.find(neighbour);


			//not occupied and not in closed hashlist
			if (!(neighbour->occupied) && u_iter == closeList.end())
			{
				int movementCost = currNode->gcost + NodeDistance(currNode, neighbour);

				Heap <A_Node*, std::vector<A_Node*>>::const_iterator v_iter2 = openList.find(neighbour);

				//movement from neighbour / is not in openlist
				if (movementCost < neighbour->gcost || v_iter2 == openList.cend()) {
					neighbour->gcost = movementCost;
					neighbour->hcost = NodeDistance(neighbour, endNode);
					neighbour->parent = currNode;

					//add to openlist if openlist doesnt contain neighbour
					if (v_iter2 == openList.cend())
						openList.push(neighbour);
				}
			}
		}
	}
}


