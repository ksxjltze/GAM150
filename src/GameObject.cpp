#include "GameObject.h"

AEVec2 StarBangBang::GameObject::GetPos()
{
	if (parent != nullptr)
	{
		AEVec2 pos;
		AEVec2Add(&pos, &parent->transform.position, &transform.position);
		return pos;
	}
	return transform.position;
}

void StarBangBang::GameObject::SetPos(AEVec2 newPos)
{
	{
		if (parent != nullptr)
		{
			AEVec2 pos;
			AEVec2Sub(&pos, &newPos, &parent->transform.position);
			transform.position = pos;
		}
		else
			transform.position = newPos;
	}
}
