#include "StealthWalk.h"
#include "globals.h"

namespace StarBangBang
{
	StealthWalk::StealthWalk(GameObject* gameObject) : Script(gameObject), image{ nullptr }, timer{ 0.0f }, cooldown{ 0.0f }
	{

	}

	void StealthWalk::Start()
	{
		image = gameObject->GetComponent<ImageComponent>();
	}

	void StealthWalk::Update()
	{
		if (AEInputCheckTriggered(AEVK_Q) && cooldown <= EPSILON)
		{
			invisible = true;
			image->SetTransparency(0.4f);
			timer = 10.0f;
			cooldown = 10.0f;
		}

		if (timer > EPSILON)
		{
			timer -= g_dt;
			if (timer <= EPSILON)
			{
				invisible = false;
				image->SetTransparency(1.0f);
			}
		}
		else if (cooldown > EPSILON)
		{
			cooldown -= g_dt;
		}
	}
}