#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
#include "Grid.h"

namespace StarBangBang
{
	
	
	namespace PathFinder
	{
		void Init();
		void SearchForPath(AEVec2 start, AEVec2 target);
		void GridDraw();
	}
	
}


