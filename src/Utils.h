#pragma once
#include "AEEngine.h"
#include "GameObject.h"
//Helper functions

namespace StarBangBang
{
	//TODO make a better manager thing
	AEVec2 GetMouseWorldPos(bool isWorld = true);
	bool CompareGameObject(GameObject* A, GameObject* B);
	bool PointRectTest(AEVec2 pointPos, AEVec2 rectCenter, float width, float height);
}