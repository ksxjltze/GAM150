#include "Key.h"
#include "CollisionEvent.h"
#include "Door.h"
#include "globals.h"

namespace StarBangBang
{
	Key::Key(GameObject* obj, Door* door) : Script(obj), door{ door }, collected{ false }
	{
		scale = gameObject->transform.scale.x;
	}

	bool Key::isCollected()
	{
		return collected;
	}

	void Key::Pickup()
	{
		gameObject->active = false;
		collected = true;
	}

	void Key::onNotify(Event e)
	{
		if (e.id == EventId::COLLISION)
		{
			CollisionEvent colEvent = std::any_cast<CollisionEvent>(e.context);
			if (colEvent.second->gameObject != gameObject)
				return;

			if (colEvent.first->gameObject->name == "Player" || colEvent.first->gameObject->name == "Client")
				Pickup();

		}
	}

	void Key::Start()
	{
		door->AddKey(this);
		collected = false;
	}

	void Key::Update()
	{
		if (!flip)
			gameObject->transform.scale.x -= g_dt;
		else
			gameObject->transform.scale.x += g_dt;

		if (gameObject->transform.scale.x < -scale)
			flip = true;
		else if (gameObject->transform.scale.x > scale)
			flip = false;
	}
}