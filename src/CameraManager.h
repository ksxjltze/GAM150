#pragma once
#include <vector>
#include "ScriptComponent.h"
#include "CameraComponent.h"
#include "ObjectManager.h"

#if 0
namespace StarBangBang
{
	class CameraManager : public Script
	{
	public:
		CameraManager(GameObject* obj);
		void AddCamera(GameObject* obj, ObjectManager& objMgr);
		void SetActiveCamera(GameObject* obj);
		void RegisterCamera(GameObject* obj);
		void Start();
		void Update();
	private:
		std::vector<CameraComponent*> cameraList;
	};
}
#endif