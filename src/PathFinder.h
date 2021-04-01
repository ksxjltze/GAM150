#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
#include "Grid.h"

namespace StarBangBang
{
	namespace PathFinder
	{
		void PathFinderInit();
		void ShowGrid(bool visible = true);
		void Free();
		void SearchForPath(AEVec2 start, AEVec2 target, std::vector<A_Node*>& pathing);
	

		void GridDraw();
		Grid& GetWorldGrid();

	}
	
}


