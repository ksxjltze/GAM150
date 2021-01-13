#include "TestState.h"

using namespace TempTeam;

TestState::TestState()
{

}

void TestState::Init()
{
	////////////////////////////////
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	object.Init();
	//////////////////////////////////
	// Creating Fonts	
	fontId = AEGfxCreateFont("../Resources/Roboto-Regular.ttf", 12);
	// Creating Fonts end
	//////////////////////////////////
}

void TestState::Update()
{
	object.Update();
}

void TempTeam::TestState::Draw()
{
	object.Draw();

	char strBuffer[100];
	memset(strBuffer, 0, 100 * sizeof(char));
	sprintf_s(strBuffer, "FPS:  %.6f", AEFrameRateControllerGetFrameRate());

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	f32 TextWidth, TextHeight;
	AEGfxGetPrintSize(fontId, strBuffer, 1.0f, TextWidth, TextHeight);
	AEGfxPrint(fontId, strBuffer, 0.99 - TextWidth, 0.99 - TextHeight, 1.0f, 1.f, 1.f, 1.f);
}

void TestState::Exit()
{
	//Free objects and textures
	AEGfxDestroyFont(fontId);
}
