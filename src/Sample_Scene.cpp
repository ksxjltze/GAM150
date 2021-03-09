#include "Sample_Scene.h"
#include "CollisionManager.h"
#include "MovementManager.h"
#include "Physics.h"
#include "CameraComponent.h"
StarBangBang::Sample_Scene::Sample_Scene(int id, GameStateManager& manager) : Scene(id, manager), gameObject{nullptr}
{
	
}

void StarBangBang::Sample_Scene::Load()
{
	image = graphicsManager.CreateSprite("../Resources/PlanetTexture.png");
	image2 = graphicsManager.CreateSprite("../Resources/boi.png");
}

void StarBangBang::Sample_Scene::Init()
{
	gameObject = objectManager.NewGameObject();

	objectManager.AddImage(gameObject, image2);
	objectManager.AddCollider(gameObject, false);

	for (int i = 0; i < 8; i++)
	{
		GameObject* obj = objectManager.NewGameObject();

		double rads = (2 * (double)PI / 8) * i;
	
		AEVec2& pos = obj->transform.position;

		if (i == 0 )
		{
			pos.x = 100.0f;
			pos.y = 0;
		}
		else if (i ==1)
		{
			pos.x = 200.0f;
			pos.y = 0;
		}
		else
		{
			pos.x = cos(rads) * 200;
			pos.y = sin(rads) * 200;

		}
		

		objectManager.AddComponent<RigidBody>(obj);
		objectManager.AddImage(obj, image);
		objectManager.AddCollider(obj, true);
		
		
	}

	objectManager.AddComponent<RigidBody>(gameObject);
	objectManager.AddComponent<CameraComponent>(gameObject);
	objectManager.AddComponent<PrimaryMovementController>(gameObject);


	//Collider* collider = CollisionManager::CreateBoxColliderInstance(gameObject);
	//objectManager.AddComponent(gameObject, collider, false);

	//MovementManager moveMgr = objectManager.AddComponent<MovementManager>(gameObject);
	//objectManager.AddComponent<PrimaryMovementController>(collisionTestObj);

	//moveMgr.AddController(gameObject);
	//moveMgr.AddController(collisionTestObj);

	objectManager.Init();
}

void StarBangBang::Sample_Scene::Update()
{
	Scene::Update();
}

void StarBangBang::Sample_Scene::Draw()
{
	Scene::Draw();
}

void StarBangBang::Sample_Scene::Free()
{
	Scene::Free();
}

void StarBangBang::Sample_Scene::Unload()
{
	Scene::Unload();
}


