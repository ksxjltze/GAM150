
#include "PathFinder.h"
#include <unordered_set>
#include <algorithm>
#include "Utils.h"
#include "BasicMeshShape.h"

using namespace StarBangBang;

const int diagonal_Cost = 14;
const int straight_Cost = 10;

void PathFinder::Init()
{
	PathFinder::grid = Grid();
}

void PathFinder::Free()
{
	PathFinder::grid.FreeGrid();
}

void PathFinder::GridDraw()
{
	AEVec2 mousePos = GetMouseWorldPos();
	Node* n = grid.GetNodeFromPosition(mousePos);
	if (n)
		StarBangBang::DrawCircle(10.0f, n->nodePos);
	PathFinder::grid.DrawGrid();
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
void TracePath( Node* start,  Node* end)
{
	std::vector<Node*> p;
	p.reserve(100);
	Node* currNode = end;
	while (currNode != start)
	{
		p.push_back(currNode);
		currNode = currNode->parent;
	}
	p.push_back(start);
	std::reverse(p.begin(), p.end());
	
	for (const Node* n : p)
	{
		DrawCircle(10.0f, n->nodePos);
	}

}
void PathFinder::SearchForPath(AEVec2 start, AEVec2 target)
{
	Node* startNode = grid.GetNodeFromPosition(start);
	Node* endNode = grid.GetNodeFromPosition(target);
	std::vector<Node*> openList;
	openList.reserve(30);
	std::unordered_set<Node*> closeList;
	closeList.reserve(30);

	//invalid positions
	if (!endNode || !startNode)
		return;
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
		openList.erase(openList.begin() + (i-1));
		//scanned nodes
		closeList.insert(currNode);

		if (currNode == endNode)
		{
			TracePath(startNode,endNode);
			return;
		}
			

		for ( Node* neighbour : grid.GetNodeNeighbours(currNode))
		{
			std::unordered_set<Node*>::const_iterator u_iter = closeList.find(neighbour);
			/*if (neighbour->occupied || u_iter != closeList.end())
				continue;

			*/
			//not occupied and not in closed hashlist
			if (!neighbour->occupied && u_iter == closeList.end())
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

