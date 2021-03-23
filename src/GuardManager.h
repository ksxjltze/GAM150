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
		const unsigned int NUM_GUARDS = 15; // to be read from file
		const unsigned int NUM_CAMERAS = 10;

	public:
		GuardManager(GameObject* gameObject);

		void Start() {};
		void Update();

		void Init(ObjectManager* objManager, Sprite* sprite, GameObject* player, GameObject* client);
		void CreateSecurityCameras(ObjectManager* objManager, Sprite* sprite, GameObject* player, GameObject* client);

		std::vector<GameObject*> GetGuards() const { return guards; }

	private:
		GameObject* GetNearestGuard(AEVec2& _pos);

		// temp
		void SetGuardWaypoints(int id, const AEVec2& start, const AEVec2& end, bool isIdle = false, float speed = GUARD::GUARD_SPEED);
		void InitSecurityCam(int id, const AEVec2& pos, float min, float max, float speed = GUARD::CAM_ROT_SPEED);

		std::vector<GameObject*> guards; //GameObject* guards[NUM_GUARDS];
		std::vector<GameObject*> cameras;
	};
}