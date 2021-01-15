#include "Drag.h"

TempTeam::Drag::Drag()
{
	enabled = false;
}

void TempTeam::Drag::Update(AEVec2 &objectPos, AEVec2 mousePos, float objectWidth, float objectHeight)
{
	//Drag object
	float mouseX = mousePos.x, mouseY = mousePos.y;
	if (AEInputCheckTriggered(AEVK_LBUTTON))
	{
		if (mouseX > objectPos.x - objectWidth / 2
			&& mouseX < objectPos.x + objectWidth / 2
			&& -mouseY > objectPos.y - objectHeight / 2
			&& -mouseY < objectPos.y + objectHeight / 2)
		{
			enabled = true;
		}

	}
	else if (AEInputCheckReleased(AEVK_LBUTTON))
	{
		enabled = false;
	}

	if (enabled)
	{
		objectPos.x = mouseX;
		objectPos.y = -mouseY;
	}
}
