#pragma once
#include "AEEngine.h"
#include "GameObject.h"
//Helper functions

namespace StarBangBang
{
	//TODO make a better manager thing
	AEVec2 GetMouseWorldPos();
	bool CompareGameObject(GameObject* A, GameObject* B);

}