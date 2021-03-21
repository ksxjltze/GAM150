#pragma once
#include "ScriptComponent.h"
#include "ObjectManager.h"
#include "Guard.h"
#include <vector>

namespace StarBangBang
{
	class ObjectManager;
	struct Sprite;

	class GuardManager : public Script
	{
	private:
		int NUM_GUARDS = 13; // to be read from file

	public:
		GuardManager(GameObject* gameObject);

		void Start() {};
		void Update();

		void Init(ObjectManager* objManager, Sprite* sprite, GameObject* player, GameObject* client);

		std::vector<GameObject*> GetGuards() const { return guards; }

	private:
		GameObject* GetNearestGuard(AEVec2& _pos);

		// temp
		void SetGuardWaypoints(const AEVec2& start, const AEVec2& end, bool isIdle = false);

		std::vector<GameObject*> guards; //GameObject* guards[NUM_GUARDS];
	};
}