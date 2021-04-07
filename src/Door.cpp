#include "Door.h"

namespace StarBangBang
{
	Door::Door(GameObject* obj) : Script(obj), parent{ nullptr }
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
		//Debug_Disable();

		std::set<Key*> keyList = keys;
		if (parent)
		{
			keyList = parent->keys;
		}

		for (auto k : keyList)
		{
			if (!k->isCollected())
				return;
		}

		gameObject->active = false;

	}

	void Door::Link(std::initializer_list<Door*> doorList)
	{
		for (auto door : doorList)
		{
			door->parent = this;
		}
	}

	void Door::Debug_Disable()
	{
		if (AEInputCheckTriggered(AEVK_K))
		{
			gameObject->active = false;
		}
	}
}