#include "Utils.h"
#include "GraphicsManager.h"

AEVec2 StarBangBang::GetMouseWorldPos()
{
	int mouseX = 0, mouseY = 0;
	AEVec2 CameraPos { 0, 0 };

	AEInputGetCursorPosition(&mouseX, &mouseY);
	AEGfxGetCamPosition(&CameraPos.x, &CameraPos.y);

	AEVec2 pos = { (float)mouseX, (float)-mouseY };
	AEMtx33 mtx;
	float zoom = GRAPHICS::GetZoom();

	AEMtx33Trans(&mtx, -AEGetWindowWidth() / 2 + CameraPos.x, AEGetWindowHeight() / 2 + CameraPos.y);
	AEMtx33ScaleApply(&mtx, &mtx, 1 / zoom, 1 / zoom);
	AEMtx33MultVec(&pos, &mtx, &pos);

	return pos;
}

bool StarBangBang::CompareGameObject(StarBangBang::GameObject* A, StarBangBang::GameObject* B)
{
	return A->transform.position.x < B->transform.position.x;
}
