#pragma once
#include "AEEngine.h"
#include "GameObject.h"
//Helper functions

namespace StarBangBang
{
	//TODO make a better manager thing
	AEVec2 GetMouseWorldPos();
	AEVec2 GetGameObjectPos(GameObject* gameObject);
	void SetGameObjectPos(GameObject* gameObject, AEVec2 newPos);
	bool CompareGameObject(GameObject* A, GameObject* B);

}