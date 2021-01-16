#include "DragComponent.h"

TempTeam::DragComponent::DragComponent(GameObject* gameObject)
{
	this->gameObject = gameObject;
	enabled = false;
}

void TempTeam::DragComponent::Update(AEVec2 mousePos)
{
	float mouseX = mousePos.x, mouseY = mousePos.y;
	AEVec2 &pos = gameObject->transform.position;
	float width = gameObject->width, height = gameObject->height;

	if (AEInputCheckTriggered(AEVK_LBUTTON))
	{
		if (mouseX > pos.x - width / 2
			&& mouseX < pos.x + width / 2
			&& -mouseY > pos.y - width / 2
			&& -mouseY < pos.y + width / 2)
		{
			enabled = true;
		}

	}
	else if (AEInputCheckReleased(AEVK_LBUTTON))
	{
		enabled = false;
	}

	if (enabled)
	{
		pos.x = mouseX;
		pos.y = -mouseY;
	}
}
