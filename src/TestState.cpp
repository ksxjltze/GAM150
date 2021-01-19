#include "TestState.h"

StarBangBang::TestState::TestState(StarBangBang::GameStateManager* gameStateManager, int id) : State(id)
{
	this->gameStateManager = gameStateManager;
	object2 = nullptr;
	object2Child = nullptr;

}

void StarBangBang::TestState::Load()
{
	object2 = objectManager.NewGameObject(100, 100);
	object2Child = objectManager.NewGameObject(50, 50);
	objectManager.AddImageComponent(object2, graphicsManager, "../Resources/PlanetTexture.png");
	objectManager.AddImageComponent(object2Child, graphicsManager, "../Resources/boi.png");

	if (fontId == 0)
		fontId = AEGfxCreateFont("../Resources/Roboto-Regular.ttf", 12);
}

void StarBangBang::TestState::Init()
{
	////////////////////////////////
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	object2->transform.position.x = 100;
	objectManager.AddDragComponent(object2);
	objectManager.AddDragComponent(object2Child);
	objectManager.AddChildGameObject(object2Child, object2);

	tileManager.Init(objectManager, graphicsManager);
}

void StarBangBang::TestState::Update()
{
	objectManager.Update();
	//Move child
	//double dt = AEFrameRateControllerGetFrameTime();
	//object2Child->transform.position.x += 100 * dt;

	if (AEInputCheckTriggered(VK_SPACE))
	{
		//State* nextState = gameStateManager->AddGameState<TestState2>();
		gameStateManager->SetNextGameState(1);
	}
}

void StarBangBang::TestState::Draw()
{
	objectManager.Draw();

	char strBuffer[100];
	memset(strBuffer, 0, 100 * sizeof(char));
	sprintf_s(strBuffer, "FPS:  %.6f", AEFrameRateControllerGetFrameRate());

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	f32 TextWidth, TextHeight;
	AEGfxGetPrintSize(fontId, strBuffer, 1.0f, TextWidth, TextHeight);
	AEGfxPrint(fontId, strBuffer, 0.99f - TextWidth, 0.99f - TextHeight, 1.0f, 1.f, 1.f, 1.f);
}

void StarBangBang::TestState::Free()
{
	//Free objects and textures
	//AEGfxDestroyFont(fontId);
	memoryManager.Free();
}

void StarBangBang::TestState::Unload()
{
	memoryManager.Unload();
}
