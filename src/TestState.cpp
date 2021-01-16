#include "TestState.h"

using namespace StarBangBang;

TestState::TestState()
{
	object = nullptr;
	object2 = nullptr;
	objectImage = nullptr;
	tileImage = nullptr;
}

void StarBangBang::TestState::Load()
{
	objectImage = objectManager.ImageLoad(graphicsManager, 100, 100, "../Resources/boi.png", 255);
	tileImage = objectManager.ImageLoad(graphicsManager, 100, 100, "../Resources/grass.png", 255);

	object2 = objectManager.NewGameObject(100, 100);
	objectManager.AddImageComponent(object2, graphicsManager, "../Resources/PlanetTexture.png");
}

void TestState::Init()
{
	////////////////////////////////
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	object = objectManager.InitTestObject(objectImage);

	object2->transform.position.x = 100;
	objectManager.AddDragComponent(object2);

	tilemap.Init();
	//////////////////////////////////
	// Creating Fonts	
	fontId = AEGfxCreateFont("../Resources/Roboto-Regular.ttf", 12);
	// Creating Fonts end
	//////////////////////////////////
}

void TestState::Update()
{
	object->Update();
	objectManager.Update();
	tilemap.Update();
}

void StarBangBang::TestState::Draw()
{
	object->Draw();
	objectManager.Draw();
	tilemap.Draw();

	char strBuffer[100];
	memset(strBuffer, 0, 100 * sizeof(char));
	sprintf_s(strBuffer, "FPS:  %.6f", AEFrameRateControllerGetFrameRate());

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	f32 TextWidth, TextHeight;
	AEGfxGetPrintSize(fontId, strBuffer, 1.0f, TextWidth, TextHeight);
	AEGfxPrint(fontId, strBuffer, 0.99f - TextWidth, 0.99f - TextHeight, 1.0f, 1.f, 1.f, 1.f);
}

void TestState::Free()
{
	//Free objects and textures
	AEGfxDestroyFont(fontId);
	object->Exit();
	tilemap.Exit();
	objectManager.FreeObjects();
}

void StarBangBang::TestState::Unload()
{
	graphicsManager.UnloadTextures();
	graphicsManager.FreeMeshes();
}
