#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
#include "Grid.h"

namespace StarBangBang
{
	
	
	namespace PathFinder
	{
		 static Grid grid;
		void Init();
		void Free();
		void SearchForPath(AEVec2 start, AEVec2 target);
		void GridDraw();
	}
	
}


