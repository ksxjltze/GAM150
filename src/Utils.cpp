#include "Utils.h"

AEVec2 StarBangBang::GetMouseWorldPos()
{
	int mouseX = 0, mouseY = 0;
	AEInputGetCursorPosition(&mouseX, &mouseY);
	mouseX -= AEGetWindowWidth() / 2;
	mouseY -= AEGetWindowHeight() / 2;
	return { (float)mouseX, (float)mouseY };
}

AEVec2 StarBangBang::GetGameObjectPos(GameObject* gameObject)
{
	if (gameObject->parent != nullptr)
	{
		AEVec2 pos;
		AEVec2Add(&pos, &gameObject->parent->transform.position, &gameObject->transform.position);
		return pos;
	}
	return gameObject->transform.position;
}

void StarBangBang::SetGameObjectPos(GameObject* gameObject, AEVec2 newPos)
{
	if (gameObject->parent != nullptr)
	{
		AEVec2 pos;
		AEVec2Sub(&pos, &newPos, &gameObject->parent->transform.position);
		gameObject->transform.position = pos;
	}
	else
		gameObject->transform.position = newPos;
}
