#include "Click.h"
#include "Utils.h"

StarBangBang::Click::Click(GameObject* obj) : Script(obj), callback{ nullptr }
{

}

void StarBangBang::Click::Start()
{

}

void StarBangBang::Click::Update()
{
	if (AEInputCheckTriggered(AEVK_LBUTTON))
	{
		Transform& transform = gameObject->transform;
		if (PointRectTest(GetMouseWorldPos(), transform.position, transform.scale.x * GRAPHICS::MESH_WIDTH, transform.scale.y * GRAPHICS::MESH_HEIGHT))
		{
			onClick();
		}

	}
	
}

void StarBangBang::Click::setCallback(void(*fptr)(void))
{
	callback = fptr;
}

void StarBangBang::Click::onClick()
{
	if (callback)
	{
		callback();
	}
}
