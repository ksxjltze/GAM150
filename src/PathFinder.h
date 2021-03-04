#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
#include "Grid.h"

namespace StarBangBang
{
	namespace PathFinder
	{
		void PathFinderInit();
		void Free();
		//std::vector<AEVec2> SearchForPath(AEVec2 start, AEVec2 target);
		std::vector<A_Node*> SearchForPath(AEVec2 start, AEVec2 target);
		void GridDraw();
		Grid& GetWorldGrid();
	}
	
}


