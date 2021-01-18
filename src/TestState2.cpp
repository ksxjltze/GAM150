#include "TestState2.h"
#include "TestState.h"

StarBangBang::TestState2::TestState2(GameStateManager* gameStateManager, int id) : State(id)
{
	object1 = nullptr;
	this->gameStateManager = gameStateManager;
}

void StarBangBang::TestState2::Load()
{
	object1 = objectManager.NewGameObject(100, 100);
	objectManager.AddImageComponent(object1, graphicsManager, "../Resources/boi.png");
}

void StarBangBang::TestState2::Init()
{
	objectManager.AddDragComponent(object1);
}

void StarBangBang::TestState2::Update()
{
	objectManager.Update();
	if(AEInputCheckTriggered(VK_SPACE))
	{
		gameStateManager->SetNextGameState(0);
	}
}

void StarBangBang::TestState2::Draw()
{
	objectManager.Draw();
}

void StarBangBang::TestState2::Free()
{
	objectManager.FreeObjects();
	objectManager.FreeComponents();
}

void StarBangBang::TestState2::Unload()
{
	graphicsManager.UnloadTextures();
	graphicsManager.FreeMeshes();
}
