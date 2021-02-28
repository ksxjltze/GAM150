#pragma once
#include "ScriptComponent.h"
#include "ObjectManager.h"
#include "Guard.h"
#include <vector>

namespace StarBangBang
{
	class GuardManager : public Script
	{
	public:
		GuardManager(GameObject* gameObject);

		void Start() {};
		void Update();
		void Init();

		inline void SetObjectManager(ObjectManager* _manager) { objectManager = _manager; }
		inline void SetSprite(Sprite* _sprite) { guard_sprite = _sprite; }

	private:
		static const int NUM_GUARDS = 1;

		GameObject* GetNearestGuard(AEVec2& _pos);

		ObjectManager* objectManager;
		Sprite* guard_sprite;
		std::vector<GameObject*>guards; //GameObject* guards[NUM_GUARDS];
	};
}