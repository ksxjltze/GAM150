#include "TestObject.h"
#include <iostream>
#include "Utils.h"

void TempTeam::TestObject::Init()
{
	transform.position.x = 0;
	transform.position.y = 0;
	transform.rotation = 0;
	transform.scale = 1;

	//image.Init("../Resources/PlanetTexture.png", 100, 100, 255);
	collider.Init(100, 100);
}

void TempTeam::TestObject::Update()
{
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

	dragComponent.Update(transform.position, GetMouseWorldPos(), 100, 100);

}

void TempTeam::TestObject::Draw()
{
	image->Draw(transform.position);
}

void TempTeam::TestObject::Exit()
{

}
