#include "TestState2.h"
#include "TestState.h"

StarBangBang::TestState2::TestState2(GameStateManager* gameStateManager, int id) : State(id)
{
	object1 = nullptr;
	this->gameStateManager = gameStateManager;
}

void StarBangBang::TestState2::Load()
{
	sprite.texture = graphicsManager.LoadTexture("../Resources/boi.png");
	sprite.mesh = graphicsManager.CreateMesh(100, 100);
}

void StarBangBang::TestState2::Init()
{
	object1 = objectManager.NewGameObject(100, 100);
	objectManager.AddImageComponent(object1, sprite);
	objectManager.AddDragComponent(object1);
}

void StarBangBang::TestState2::Update()
{
	objectManager.Update();
	if(AEInputCheckTriggered(VK_SPACE))
	{
		gameStateManager->SetNextGameState(2);
		//gameStateManager->ReloadGameState();
	}
}

void StarBangBang::TestState2::Draw()
{
	objectManager.Draw();
}

void StarBangBang::TestState2::Free()
{
	memoryManager.Free();
}

void StarBangBang::TestState2::Unload()
{
	memoryManager.Unload();
}
