#include "Level_Demo.h"

StarBangBang::Level_Demo::Level_Demo(GameStateManager* manager, int id) : State(id)
{
	player = nullptr;
	gameStateManager = manager;
}

void StarBangBang::Level_Demo::Load()
{
	playerImage.texture = graphicsManager.LoadTexture("../Resources/boi.png");
	playerImage.mesh = graphicsManager.CreateMesh(100, 100);
}

void StarBangBang::Level_Demo::Init()
{
	player = objectManager.NewGameObject(100, 100);
	objectManager.AddImageComponent(player, playerImage);
	objectManager.AddComponent<DragComponent>(player);
	scriptManager.AddScript<Player>(player);

	player2 = objectManager.CloneGameObject(player);
	player2->transform.position.x += 100;
}

void StarBangBang::Level_Demo::Update()
{
	State::Update();
}

void StarBangBang::Level_Demo::Draw()
{
	State::Draw();

}

void StarBangBang::Level_Demo::Free()
{

}

void StarBangBang::Level_Demo::Unload()
{

}
