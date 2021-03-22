#include "CameraManager.h"

#if 0

StarBangBang::CameraManager::CameraManager(GameObject* obj) : Script(obj)
{

}

void StarBangBang::CameraManager::AddCamera(GameObject* obj, ObjectManager& objMgr)
{
	objMgr.AddComponent<CameraComponent>();
	CameraComponent* cam = obj->GetComponent<CameraComponent>();
	if (cam)
		cameraList.push_back(cam);
}

void StarBangBang::CameraManager::SetActiveCamera(GameObject* obj)
{
	for (auto cam : cameraList)
	{
		cam->active = false;

		if (cam->gameObject == obj)
		{
			cam->active = true;
		}
	}
}

void StarBangBang::CameraManager::RegisterCamera(GameObject* obj)
{

}

void StarBangBang::CameraManager::Start()
{

}

void StarBangBang::CameraManager::Update()
{
	
}
#endif
