/******************************************************************************/
/*!
\title		Captain Stealth
\file		Utils.cpp
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Global Utility functions.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#include "Utils.h"
#include "GraphicsManager.h"

namespace StarBangBang
{
	AEVec2 GetMouseWorldPos(bool isWorld)
	{
		int mouseX = 0, mouseY = 0;
		AEVec2 CameraPos { 0, 0 };

		AEInputGetCursorPosition(&mouseX, &mouseY);
		AEVec2 pos = { (float)mouseX, (float)-mouseY };
		AEMtx33 mtx;

		float winWidth = static_cast<float>(AEGetWindowWidth());
		float winHeight = static_cast<float>(AEGetWindowHeight());

		if (isWorld)
		{
			CameraPos = GRAPHICS::GetCameraPosition();
			float zoom = GRAPHICS::GetZoom();

			AEMtx33Trans(&mtx, -winWidth / 2 + CameraPos.x, winHeight / 2 + CameraPos.y);
			AEMtx33ScaleApply(&mtx, &mtx, 1 / zoom, 1 / zoom);
		}
		else
			AEMtx33Trans(&mtx, -winWidth / 2, winHeight / 2);
		GRAPHICS::InverseScaleFullscreen(mtx);

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
