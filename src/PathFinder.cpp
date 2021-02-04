
#include "PathFinder.h"
#include <unordered_set>
#include "Utils.h"
#include "BasicMeshShape.h"
using namespace StarBangBang;

Grid grid;

void PathFinder::Init()
{
	grid = Grid();
}
void PathFinder::GridDraw()
{
	AEVec2 mousePos = GetMouseWorldPos();
	Node* n = grid.GetNodeFromPosition(mousePos);
	if (n)
		StarBangBang::DrawCircle(10.0f, n->nodePos);
	grid.DrawGrid();
}
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

