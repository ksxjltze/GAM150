#include "Key.h"
#include "CollisionEvent.h"
#include "Door.h"

namespace StarBangBang
{
	Key::Key(GameObject* obj, Door* door) : Script(obj), door{ door }, collected{ false }
	{

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

			if (colEvent.first->gameObject->name != "Player")
				return;
			else
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
	
	}
}