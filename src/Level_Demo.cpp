#include "Level_Demo.h"

StarBangBang::Level_Demo::Level_Demo(GameStateManager* manager, int id) : State(id)
{
	gameStateManager = manager;
}

void StarBangBang::Level_Demo::Load()
{
	player.Load(graphicsManager);
}

void StarBangBang::Level_Demo::Init()
{
	player.Start(objectManager);
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
