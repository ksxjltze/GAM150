#include "Sample_Scene.h"
#include "CollisionManager.h"
#include "MovementManager.h"

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
	GameObject* collisionTestObj = objectManager.NewGameObject();

	objectManager.AddImage(gameObject, image);
	objectManager.AddCollider(gameObject, false);

	collisionTestObj->transform.position.x += 300;
	objectManager.AddImage(collisionTestObj, image2);
	objectManager.AddCollider(collisionTestObj, false);


	//Collider* collider = CollisionManager::CreateBoxColliderInstance(gameObject);
	//objectManager.AddComponent(gameObject, collider, false);

	//MovementManager moveMgr = objectManager.AddComponent<MovementManager>(gameObject);
	objectManager.AddComponent<PrimaryMovementController>(gameObject);
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


