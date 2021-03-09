#include "Utils.h"
#include "GraphicsManager.h"

namespace StarBangBang
{
	AEVec2 GetMouseWorldPos()
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

	bool CompareGameObject(GameObject* A, GameObject* B)
	{
		return A->transform.position.x < B->transform.position.x;
	}

	bool PointRectTest(AEVec2 pointPos, AEVec2 rectCenter, float width, float height)
	{
		AEVec2 min{ 0, 0 }, max{ 0, 0 };
		AEVec2 halfExtents = { width / 2, height / 2 };

		AEVec2Sub(&min, &rectCenter, &halfExtents);
		AEVec2Add(&max, &rectCenter, &halfExtents);

		if (pointPos.x < min.x || pointPos.x > max.x || pointPos.y < min.y || pointPos.y > max.y)
		{
			return false;
		}
		return true;

	}

}
