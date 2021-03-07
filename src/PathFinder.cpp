
#include "PathFinder.h"
#include <unordered_set>
#include <algorithm>
#include "Utils.h"
#include "BasicMeshShape.h"
#include <iostream>

using namespace StarBangBang;

const int diagonal_Cost = 14;
const int straight_Cost = 10;

Grid worldGrid;

void PathFinder::PathFinderInit()
{
	worldGrid.CreateGrid(64,50,50, AEVec2{ 0,0 });
}

void PathFinder::Free()
{
	worldGrid.FreeGrid();
}

void PathFinder::GridDraw()
{
	AEVec2 mousePos = GetMouseWorldPos();
	A_Node* n = worldGrid.GetNodeFromPosition(mousePos);
	if (n)
		StarBangBang::DrawCircle(10.0f, n->nodePos);
	worldGrid.DrawGrid();
}

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
void TracePath(A_Node* start, A_Node* end , std::vector<A_Node*>& p)
{
	
	A_Node* currNode = end;
	while (currNode != start)
	{
		p.push_back(currNode);
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
std::vector<A_Node*> PathFinder::SearchForPath(AEVec2 start, AEVec2 target)
{
	std::vector<A_Node*> pathing;
	pathing.reserve(100);

	A_Node* startNode = worldGrid.GetNodeFromPosition(start);
	A_Node* endNode = worldGrid.GetNodeFromPosition(target);
	std::vector<A_Node*> openList;
	openList.reserve(30);
	std::unordered_set<A_Node*> closeList;
	closeList.reserve(30);

	//invalid positions
	if (!endNode || !startNode)
		return pathing;
	if (endNode->occupied)
	{
		PRINT("End node occupied\n");
		return pathing;
	}
		
	openList.push_back(startNode);

	while (openList.size() > 0)
	{
		A_Node* currNode = openList[0];
		size_t i = 1;
		for (i ; i < openList.size(); i++)
		{
			//if the total cost is lesser 
			//OR the total cost is equal but the cost to from curr the target node is lesser
			if (openList[i]->GetfCost() < currNode->GetfCost()
				|| openList[i]->GetfCost() == currNode->GetfCost() && openList[i]->hcost < currNode->hcost)
			{
				currNode = openList[i];
			}
			
		}
		openList.erase(std::remove(openList.begin(), openList.end(), currNode), openList.end());
		//scanned nodes
		closeList.insert(currNode);

		if (currNode == endNode)
		{
			TracePath(startNode,endNode, pathing);
			return pathing;
		}
			

		for (A_Node* neighbour : worldGrid.Get4_NodeNeighbours(currNode))
		{
			std::unordered_set<A_Node*>::const_iterator u_iter = closeList.find(neighbour);
			
			
			//not occupied and not in closed hashlist
			if (!(neighbour->occupied) && u_iter == closeList.end())
			{
				int movementCost = currNode->gcost + NodeDistance(currNode, neighbour);

				std::vector<A_Node*>::const_iterator v_iter2 = (std::find(openList.begin(), openList.end(), neighbour));

				//movement from neighbour / is not in openlist
				if (movementCost < neighbour->gcost || v_iter2 == openList.end()) {
					neighbour->gcost = movementCost;
					neighbour->hcost = NodeDistance(neighbour, endNode);
					neighbour->parent = currNode;

					//add to openlist if openlist doesnt contain neighbour
					if (v_iter2 == openList.end())
						openList.push_back(neighbour);
				}
			}
		}
	}
	return pathing;
}

