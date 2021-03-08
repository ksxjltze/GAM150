// ---------------------------------------------------------------------------
// includes

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "AEEngine.h"
#include "AudioEngine.h"

#include "GameStateManager.h"
#include "constants.h"

#include "BasicMeshShape.h"
#include "CollisionTest.h"

#include "Level_Demo.h"
#include "Sample_Scene.h"
#include "LevelEditor.h"
#include "CaptainStealth.h"
#include "Main_Menu.h"

// ---------------------------------------------------------------------------
// main

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	///////////////////////
	// Variable declaration

	using namespace StarBangBang;
	int gGameRunning = 1;
	s8 fontId = -1;

	AudioEngine audioEngine;
	FMOD::Sound* sound = nullptr;
	audioEngine.CreateSound(&sound, "../Resources/drumloop.wav"); //CHANGE THIS (copyright and stuff)
	//audioEngine.playSound(sound, false);

	GameStateManager gameStateManager;

	//

	// Variable declaration end
	///////////////////////////


	/////////////////
	// Initialization

	// Add Game States/Scenes

	Scene* sceneDemo = gameStateManager.AddGameState<Level_Demo>(SCENE::DEMO);
	Scene* sceneEditor = gameStateManager.AddGameState<LevelEditor>(SCENE::EDITOR);
	Scene* sampleScene = gameStateManager.AddGameState<Sample_Scene>(SCENE::SAMPLE);
	Scene* gameScene = gameStateManager.AddGameState<CaptainStealth>(SCENE::GAME);
	Scene* mainMenuScene = gameStateManager.AddGameState<Main_Menu>(SCENE::MAINMENU);

	UNREFERENCED_PARAMETER(sceneEditor);
	UNREFERENCED_PARAMETER(sceneDemo);
	UNREFERENCED_PARAMETER(sampleScene);
	UNREFERENCED_PARAMETER(gameScene);

	// Set Initial State

	gameStateManager.SetInitialState(sampleScene);

	//// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 800, 600, 1, 60, true, NULL);
	StarBangBang::InitBasicMesh();
	
	PathFinder::PathFinderInit();
	//Full screen
	//AESysInit(hInstance, nCmdShow, 1920, 1080, 1, 60, true, NULL);
	//AEToogleFullScreen(true);

	// Changing the window title
	AESysSetWindowTitle("Captain Stealth");

	// reset the system modules
	AESysReset();

	AEGfxSetBackgroundColor(0.3f, 0.6f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	// ALWAYS CREATE FONTS OUTSIDE LOOP
	fontId = AEGfxCreateFont("../Resources/Roboto-Regular.ttf", 12);
	if (fontId < 0)
	{
		fontId = 0;
		AE_ASSERT_MESG(fontId, "FAILED TO CREATE FONT");
	}

	// Initialization end
	/////////////////////

	//Game Loop
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

		StarBangBang::TestGrid();
		CollisionManager::ResolverUpdate();
		StarBangBang::PathFinderTest();

		// Update State
		gameStateManager.Update();
		audioEngine.Update();
		
		//FPS
		AEVec2 camPos;
		AEGfxGetCamPosition(&camPos.x, &camPos.y);

		char strBuffer[100];
		memset(strBuffer, 0, 100 * sizeof(char));
		sprintf_s(strBuffer, "FPS:  %.6f", AEFrameRateControllerGetFrameRate());

		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		f32 TextWidth, TextHeight;
		AEGfxGetPrintSize(fontId, strBuffer, 1.0f, TextWidth, TextHeight);
		AEGfxPrint(fontId, strBuffer, 0.99f - TextWidth, 0.99f - TextHeight, 1.0f, 1.f, 1.f, 1.f);

		//StarBangBang::Test_BoxUpdate();
		//StarbangBang::Test_CircleUpdate();
		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}


	FreeTest();
	//Audio Engine (temp implementation)
	audioEngine.ReleaseSound(sound);
	audioEngine.Exit();


	//free font
	AEGfxDestroyFont(fontId);

	//free the system
	AESysExit();


}