#pragma once
#include "ScriptComponent.h"
#include "ObjectManager.h"
#include "Guard.h"
#include "Listener.h"
#include <vector>

namespace StarBangBang
{
	class ObjectManager;
	struct Sprite;

	class GuardManager : public Script, Listener
	{
	private:
		const unsigned int NUM_GUARDS = 23; // to be read from file
		const unsigned int NUM_CAMERAS = 1;

	public:
		GuardManager(GameObject* gameObject);

		void Start() {};
		void Update();
		void onNotify(Event e);

		void Init(ObjectManager* objManager, Sprite* sprite, GameObject* player, GameObject* client);
		void CreateSecurityCameras(ObjectManager* objManager, Sprite* sprite, GameObject* player, GameObject* client);

		std::vector<GameObject*> GetGuards() const { return guards; }

	private:
		GameObject* GetNearestGuard(const AEVec2& _pos, unsigned int roomNum);

		// temp
		void SetGuardStartEnd(int id, unsigned int roomNum, const AEVec2& start, const AEVec2& end, bool isIdle = false, float speed = GUARD::GUARD_SPEED);
		void SetGuardWaypoints(int id, unsigned int roomNum, const std::vector<AEVec2>& waypoints, float speed = GUARD::GUARD_SPEED);
		void InitSecurityCam(int id, unsigned int roomNum, const AEVec2& pos, float min, float max, float speed = GUARD::CAM_ROT_SPEED);

		std::vector<GameObject*> guards; //GameObject* guards[NUM_GUARDS];
		std::vector<GameObject*> cameras;
	};
}