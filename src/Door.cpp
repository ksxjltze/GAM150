#include "Door.h"

namespace StarBangBang
{
	Door::Door(GameObject* obj) : Script(obj)
	{

	}

	void Door::AddKey(Key* k)
	{
		keys.insert(k);
	}

	void Door::Start()
	{
		for (auto k : keys)
		{
			k->gameObject->active = true;
		}
	}

	void Door::Update()
	{
		for (auto k : keys)
		{
			if (!k->isCollected())
				return;
		}

		gameObject->active = false;
	}
}