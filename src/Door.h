#pragma once
#include "ScriptComponent.h"
#include "Key.h"
#include <set>
#include <initializer_list>

namespace StarBangBang
{
	class Door : public Script
	{
	public:
		Door(GameObject* obj);
		void AddKey(Key* k);
		void Start();
		void Update();

		void Link(std::initializer_list<Door*> doorList);
	private:
		Door* parent;
		std::set<Key*> keys;
	};
}