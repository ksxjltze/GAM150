#include "Utils.h"

AEVec2 StarBangBang::GetMouseWorldPos()
{
	int mouseX = 0, mouseY = 0;
	AEVec2 CameraPos { 0, 0 };

	AEInputGetCursorPosition(&mouseX, &mouseY);
	AEGfxGetCamPosition(&CameraPos.x, &CameraPos.y);

	//mouseX -= AEGetWindowWidth() / 2;
	//mouseY -= AEGetWindowHeight() / 2;

	mouseX = mouseX - AEGetWindowWidth() / 2 + CameraPos.x;
	mouseY = mouseY - AEGetWindowHeight() / 2 - CameraPos.y;

	return { (float)mouseX, (float)mouseY };
}

bool StarBangBang::CompareGameObject(StarBangBang::GameObject* A, StarBangBang::GameObject* B)
{
	return A->transform.position.x < B->transform.position.x;
}
