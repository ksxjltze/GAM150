#include "Movement.h"
#include "globals.h"

StarBangBang::Movement::Movement(GameObject* gameObject) : Script(gameObject)
{

}

void StarBangBang::Movement::Start()
{

}

void StarBangBang::Movement::Update()
{
	
	float speed = PLAYER::PLAYER_SPEED * g_dt;
	if (AEInputCheckCurr(AEVK_W))
	{
		gameObject->transform.position.y += speed;
	}

	if (AEInputCheckCurr(AEVK_A))
	{
		gameObject->transform.position.x += -speed;
	}

	if (AEInputCheckCurr(AEVK_S))
	{
		gameObject->transform.position.y += -speed;
	}

	if (AEInputCheckCurr(AEVK_D))
	{
		gameObject->transform.position.x += speed;
	}

}
