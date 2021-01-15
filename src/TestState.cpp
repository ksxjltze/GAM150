#include "TestState.h"

using namespace TempTeam;

TestState::TestState()
{
	object = nullptr;
}

void TempTeam::TestState::Load()
{
	object = objectManager.LoadTestObject(&graphicsManager, 100, 100, "../Resources/boi.png");
}

void TestState::Init()
{
	////////////////////////////////
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	object->Init();
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
	tilemap.Update();
}

void TempTeam::TestState::Draw()
{
	object->Draw();
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

void TempTeam::TestState::Unload()
{
	graphicsManager.UnloadTextures();
	graphicsManager.FreeMeshes();
}
