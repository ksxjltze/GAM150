#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
#include "Grid.h"

namespace StarBangBang
{
	namespace PathFinder
	{
		
		void Free();
		std::vector<Node*>  SearchForPath(AEVec2 start, AEVec2 target);
		void GridDraw();
		static Grid worldGrid;
	}
	
}


