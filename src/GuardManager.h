#pragma once
#include "ScriptComponent.h"
#include "ObjectManager.h"
#include <vector>

namespace StarBangBang
{
	class GuardManager : public Script
	{
	public:
		//GuardManager(ObjectManager& _manager, Sprite& _sprite);
		GuardManager(GameObject* gameObject);
		//~GuardManager();

		void Start() {};
		void Update();
		void Init();

		inline void SetObjectManager(ObjectManager* _manager) { objectManager = _manager; }
		inline void SetSprite(Sprite* _sprite) { guard_sprite = _sprite; }

	private:
		static const int NUM_GUARDS = 2;

		ObjectManager* objectManager;
		Sprite* guard_sprite;
		std::vector<GameObject*>guards; //GameObject* guards[NUM_GUARDS];
	};
}