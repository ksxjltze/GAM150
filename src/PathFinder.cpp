#include "Grid.h"
#include "PathFinder.h"
#include <unordered_set>
using namespace StarBangBang;


void PathFinder::SearchForPath(AEVec2 start, AEVec2 target)
{
	Node* startNode = grid.GetNodeFromPosition(start);
	Node* endNode = grid.GetNodeFromPosition(target);
	std::vector<Node*> openList;
	openList.reserve(30);
	std::unordered_set<Node*> closeList;
	closeList.reserve(30);
	//invalid target position
	if (!endNode)
		return;

	while (openList.size() > 0)
	{
		Node* curr = openList[0];
		size_t i = 1;
		for (i ; i < openList.size(); i++)
		{
			//if the total cost is lesser 
			//OR the total cost is equal but the cost to the target node is lesser
			if (openList[i]->GetfCost() < curr->GetfCost() 
				|| openList[i]->GetfCost() == curr->GetfCost() && openList[i]->hcost < curr->hcost)
			{
				curr = openList[i];
			}
			
		}
		openList.erase(openList.begin() + i);
		//scanned nodes
		closeList.insert(curr);

		if (curr == endNode)
			return;
	}

}

