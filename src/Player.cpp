#include "Player.h"

StarBangBang::Player::Player(GameObject* gameObject) : Script(gameObject)
{

}

void StarBangBang::Player::Load()
{
;
}

void StarBangBang::Player::Start()
{

}

void StarBangBang::Player::Update()
{
	if (AEInputCheckCurr(AEVK_W))
	{
		gameObject->transform.position.y += 10;
	}
	if (AEInputCheckCurr(AEVK_A))
	{
		gameObject->transform.position.x -= 10;
	}
	if (AEInputCheckCurr(AEVK_S))
	{
		gameObject->transform.position.y -= 10;
	}
	if (AEInputCheckCurr(AEVK_D))
	{
		gameObject->transform.position.x += 10;
	}
}
