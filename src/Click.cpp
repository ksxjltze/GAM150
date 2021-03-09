#include "Click.h"
#include "Utils.h"

StarBangBang::Click::Click(GameObject* obj, void (*fptr)(void)) : Script(obj), callback{ fptr }
{

}

void StarBangBang::Click::Start()
{
	PRINT("CLICK: START\n");
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
