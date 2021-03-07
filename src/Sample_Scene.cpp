#include "Sample_Scene.h"
#include "CollisionManager.h"

StarBangBang::Sample_Scene::Sample_Scene(int id, GameStateManager& manager) : Scene(id, manager), gameObject{nullptr}
{
	
}

void StarBangBang::Sample_Scene::Load()
{
	image = graphicsManager.CreateSprite("../Resources/PlanetTexture.png");
}

void StarBangBang::Sample_Scene::Init()
{
	gameObject = objectManager.NewGameObject();
	objectManager.AddImage(gameObject, image);
	Collider* collider = CollisionManager::CreateBoxColliderInstance(gameObject);
	objectManager.AddComponent(gameObject, collider, false);

	//objectManager.AddComponent<PrimaryMovementController>(gameObject);
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


