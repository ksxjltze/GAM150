#pragma once
#include "ScriptComponent.h"
#include "ObjectManager.h"
#include "Guard.h"
#include <vector>

namespace StarBangBang
{
	class GuardManager : public Script
	{
	private:
		const int NUM_GUARDS = 1;
	public:
		GuardManager(GameObject* gameObject);

		void Start() {};
		void Update();

		void Init(ObjectManager* objManager, Sprite* sprite);

	private:
		GameObject* GetNearestGuard(AEVec2& _pos);

		std::vector<GameObject*>guards; //GameObject* guards[NUM_GUARDS];
	};
}