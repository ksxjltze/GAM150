#pragma once
#include "AEEngine.h"

namespace TempTeam
{
	class Drag
	{
	public:
		Drag();
		void Update(AEVec2 &objectPos, AEVec2 mousePos, float objectWidth, float objectHeight);
	private:
		bool enabled;
	};
}