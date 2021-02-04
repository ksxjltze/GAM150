#include "Sample_Scene.h"

StarBangBang::Sample_Scene::Sample_Scene(GameStateManager* manager, int id) : State(id)
{
	gameStateManager = manager;
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
	State::Update();
}

void StarBangBang::Sample_Scene::Draw()
{
	State::Draw();
}

void StarBangBang::Sample_Scene::Free()
{
	State::Free();
}

void StarBangBang::Sample_Scene::Unload()
{
	State::Free();
}


