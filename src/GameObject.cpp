#include "GameObject.h"
#include "constants.h"

StarBangBang::GameObject::GameObject()
{
	active = true;
	transform.scale = { CONSTANTS::DEFAULT_OBJECT_SCALE,  CONSTANTS::DEFAULT_OBJECT_SCALE };
	transform.rotation = 0;
	transform.position = { 0, 0 };
}

StarBangBang::GameObject::GameObject(const GameObject& obj)
{
	transform = obj.transform;
	parent = obj.parent;
	width = obj.width;
	height = obj.height;
	active = obj.active;
}

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
