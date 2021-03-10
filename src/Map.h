#pragma once
#include "ScriptComponent.h"

namespace StarBangBang
{
	class ObjectManager;
	struct Sprite;

	class Map : public Script
	{
	public:
		Map(GameObject* gameObject);

		void Start();
		void Update();

		void Init(int mapWidth, int mapHeight, GameObject* _player, ObjectManager* manager, Sprite* sprite);

	private:
		AEVec2 GlobalToLocalCoord(AEVec2 pos);

		int width;
		int height;

		GameObject* player;
		GameObject* testIndicator;
	};
}