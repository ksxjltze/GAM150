#include "TestObject.h"
#include <iostream>

void TempTeam::TestObject::Init()
{
	transform.position.x = 0;
	transform.position.y = 0;
	transform.rotation = 0;
	transform.scale = 1;
	drag = false;

	image.Init("../Resources/PlanetTexture.png", 100, 100, 255);
	collider.Init(100, 100);
}

void TempTeam::TestObject::Update()
{
	int mouseX = 0, mouseY = 0;
	AEInputGetCursorPosition(&mouseX, &mouseY);

	if (AEInputCheckCurr(AEVK_W))
	{
		transform.position.y += 10;
	}
	else if (AEInputCheckCurr(AEVK_S))
	{
		transform.position.y -= 10;
	}
	if (AEInputCheckCurr(AEVK_A))
	{
		transform.position.x -= 10;
	}
	else if (AEInputCheckCurr(AEVK_D))
	{
		transform.position.x += 10;
	}

	//Drag object
	if (AEInputCheckCurr(AEVK_LBUTTON))
	{
		if (mouseX > transform.position.x - collider.width / 2
			&& mouseX < transform.position.x + collider.width / 2
			&& -mouseY > transform.position.y - collider.height / 2
			&& -mouseY < transform.position.y + collider.height / 2)
		{
			drag = true;
		}

	}
	else if (AEInputCheckReleased(AEVK_LBUTTON))
	{
		drag = false;
	}
	
	if (drag)
	{
		transform.position.x = mouseX;
		transform.position.y = -mouseY;
	}
}

void TempTeam::TestObject::Draw()
{
	image.Draw(transform.position);
}

void TempTeam::TestObject::Exit()
{
	image.Exit();
}
