#pragma once
#include "ScriptComponent.h"
#include "Key.h"
#include <set>

namespace StarBangBang
{
	class Door : public Script
	{
	public:
		Door(GameObject* obj);
		void AddKey(Key* k);
		void Start();
		void Update();
	private:
		std::set<Key*> keys;
	};
}