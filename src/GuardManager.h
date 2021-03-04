#pragma once
#include "ScriptComponent.h"
#include "ObjectManager.h"
#include "Guard.h"
#include <vector>

namespace StarBangBang
{
	class ObjectManager;
	class Sprite;

	class GuardManager : public Script
	{
	public:
		GuardManager(GameObject* gameObject);

		void Start() {};
		void Update();

		void Init(ObjectManager* objManager, Sprite* sprite, GameObject* player, GameObject* client);

	private:
		int NUM_GUARDS = 1; // to be read from file

		GameObject* GetNearestGuard(AEVec2& _pos);

		std::vector<GameObject*>guards; //GameObject* guards[NUM_GUARDS];
	};
}