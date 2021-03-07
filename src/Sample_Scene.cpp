#include "Sample_Scene.h"
#include "Collider.h"

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
	objectManager.AddComponent<BoxCollider>(gameObject);
	objectManager.AddComponent<PrimaryMovementController>(gameObject);
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


