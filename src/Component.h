#pragma once
#include "GameObject.h"
#include "constants.h"

namespace StarBangBang
{
	class ObjectManager;

	class GameComponent
	{
	public:
		GameComponent(GameObject* gameObject) { this->gameObject = gameObject; }
		virtual GameComponent* Clone(GameObject* obj, GameComponent*) const { return new GameComponent(obj); }
		virtual void Start() {};
		virtual void Update() {};
		virtual void Draw() {};
		virtual void LateUpdate() {};
		GameObject* gameObject { nullptr };
		virtual ~GameComponent() {}
		bool drawable{ false };
		bool active { true };
		ObjectManager* objMgr{ nullptr };

	};
}