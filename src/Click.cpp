#include "Click.h"
#include "Utils.h"

StarBangBang::Click::Click(GameObject* obj) : Script(obj)
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

void StarBangBang::Click::onClick()
{

}
