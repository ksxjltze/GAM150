#include "Sample_Scene.h"
#include "CollisionManager.h"
#include "MovementManager.h"
#include "Click.h"

void Testt()
{
	PRINT("TESTES\n");
}

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

	//objectManager.AddImage(gameObject, image2);
	objectManager.AddComponent<ImageComponent>(gameObject, image2);
	objectManager.AddCollider(gameObject, false);
	//objectManager.AddComponent<Click>(gameObject).setCallback(Testt);

	Click* click = gameObject->GetComponent<Click>();
	if (!click)
	{
		PRINT("CLICK NO");
	}

	for (int i = 0; i < 8; i++)
	{
		GameObject* obj = objectManager.NewGameObject();

		double rads = (2 * (double)PI / 8) * i;
		AEVec2& pos = obj->transform.position;

		pos.x = static_cast<float>(cos(rads) * 200);
		pos.y = static_cast<float>(sin(rads) * 200);

		objectManager.AddImage(obj, image);
		objectManager.AddCollider(obj, true);
		
	}


	objectManager.AddComponent<PrimaryMovementController>(gameObject);


	//Collider* collider = CollisionManager::CreateBoxColliderInstance(gameObject);
	//objectManager.AddComponent(gameObject, collider, false);

	//MovementManager moveMgr = objectManager.AddComponent<MovementManager>(gameObject);
	//objectManager.AddComponent<PrimaryMovementController>(collisionTestObj);

	//moveMgr.AddController(gameObject);
	//moveMgr.AddController(collisionTestObj);


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


