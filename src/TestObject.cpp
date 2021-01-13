#include "TestObject.h"

void TempTeam::TestObject::Init()
{
	transform.position.x = 0;
	transform.position.y = 0;
	transform.rotation = 0;
	transform.scale = 1;

	image.Init("../Resources/PlanetTexture.png", 50, 50, 255);
}

void TempTeam::TestObject::Update()
{

}

void TempTeam::TestObject::Draw()
{
	image.Draw(transform.position);
}

void TempTeam::TestObject::Exit()
{
	image.Exit();
}
