#include "Sample_Scene.h"

StarBangBang::Sample_Scene::Sample_Scene(int id, GameStateManager& manager) : Scene(id, manager)
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
	Scene::Free();
}


