#include "Utils.h"

AEVec2 TempTeam::GetMouseWorldPos()
{
	int mouseX = 0, mouseY = 0;
	AEInputGetCursorPosition(&mouseX, &mouseY);
	mouseX -= AEGetWindowWidth() / 2;
	mouseY -= AEGetWindowHeight() / 2;
	return { (float)mouseX, (float)mouseY };
}
