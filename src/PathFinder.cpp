
#include "PathFinder.h"
#include <unordered_set>
#include <algorithm>
#include "Utils.h"
#include "BasicMeshShape.h"
#include <iostream>

using namespace StarBangBang;

const int diagonal_Cost = 14;
const int straight_Cost = 10;

//Grid worldGrid;

void PathFinder::Free()
{
	PathFinder::worldGrid.FreeGrid();
}

void PathFinder::GridDraw()
{
	AEVec2 mousePos = GetMouseWorldPos();
	Node* n = worldGrid.GetNodeFromPosition(mousePos);
	if (n)
		StarBangBang::DrawCircle(10.0f, n->nodePos);
	PathFinder::worldGrid.DrawGrid();
}

int NodeDistance(const Node* lhs, const Node* rhs)
{
	int distX = abs(lhs->index_x - rhs->index_x);
	int distY = abs(lhs->index_y - rhs->index_y);

	if (distX > distY)
	{
		return  distY * diagonal_Cost + (distX - distY) * straight_Cost;
	}
	
	return distX * diagonal_Cost + (distY - distX) * straight_Cost;
	
}
void TracePath( Node* start,  Node* end , std::vector<Node*>& p)
{
	
	Node* currNode = end;
	while (currNode != start)
	{
		p.push_back(currNode);
		currNode = currNode->parent;
	}
	p.push_back(start);
	std::reverse(p.begin(), p.end());

}
std::vector<Node*> PathFinder::SearchForPath(AEVec2 start, AEVec2 target)
{
	std::vector<Node*> pathing;
	pathing.reserve(100);

	Node* startNode = PathFinder::worldGrid.GetNodeFromPosition(start);
	Node* endNode = PathFinder::worldGrid.GetNodeFromPosition(target);
	std::vector<Node*> openList;
	openList.reserve(30);
	std::unordered_set<Node*> closeList;
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
		Node* currNode = openList[0];
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
			

		for ( Node* neighbour : PathFinder::worldGrid.GetNodeNeighbours(currNode))
		{
			std::unordered_set<Node*>::const_iterator u_iter = closeList.find(neighbour);
			
			
			//not occupied and not in closed hashlist
			if (!(neighbour->occupied) && u_iter == closeList.end())
			{
				int movementCost = currNode->gcost + NodeDistance(currNode, neighbour);

				std::vector<Node*>::const_iterator v_iter2 = (std::find(openList.begin(), openList.end(), neighbour));

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

}

