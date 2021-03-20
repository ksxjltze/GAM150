// ---------------------------------------------------------------------------
// includes

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "AEEngine.h"
#include "AudioEngine.h"

#include "GameStateManager.h"
#include "constants.h"
#include "SceneList.h"

#include "BasicMeshShape.h"
#include "CollisionTest.h"
#include "globals.h"

#include "MessageBus.h"

namespace StarBangBang
{
	float g_dt = 0;
	s8 fontId = -1;
}

// ---------------------------------------------------------------------------
// main

namespace StarBangBang
{
	void DisplayFps()
	{
		char strBuffer[100];
		memset(strBuffer, 0, 100 * sizeof(char));
		sprintf_s(strBuffer, "FPS:  %.6f", AEFrameRateControllerGetFrameRate());

		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		f32 TextWidth, TextHeight;
		AEGfxGetPrintSize(fontId, strBuffer, 1.0f, TextWidth, TextHeight);
		AEGfxPrint(fontId, strBuffer, 0.99f - TextWidth, 0.99f - TextHeight, 1.0f, 1.f, 1.f, 1.f);
	}

}

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

	AudioEngine audioEngine;
	FMOD::Sound* sound = nullptr;
	audioEngine.CreateSound(&sound, "./Resources/drumloop.wav"); //CHANGE THIS (copyright and stuff)
	audioEngine.AddSound("Test", sound); //CHANGE THIS (copyright and stuff)
	audioEngine.playSound("Test", false);

	GameStateManager gameStateManager;

	//

	// Variable declaration end
	///////////////////////////


	/////////////////
	// Initialization

	// Add Game States/Scenes
	std::vector<Scene*> sceneList;

	Scene* sceneDemo		= gameStateManager.AddGameState<Level_Demo>(SceneID::DEMO);
	Scene* sceneEditor		= gameStateManager.AddGameState<LevelEditor>(SceneID::EDITOR);
	Scene* sampleScene		= gameStateManager.AddGameState<Sample_Scene>(SceneID::SAMPLE);
	Scene* gameScene		= gameStateManager.AddGameState<CaptainStealth>(SceneID::GAME);
	Scene* mainMenuScene	= gameStateManager.AddGameState<Main_Menu>(SceneID::MAIN_MENU);
	Scene* engineProof		= gameStateManager.AddGameState<EngineProof>();

	sceneList.push_back(sceneDemo);
	sceneList.push_back(sceneEditor);
	sceneList.push_back(sampleScene);
	sceneList.push_back(gameScene);
	sceneList.push_back(mainMenuScene);
	sceneList.push_back(engineProof);

	// Set Initial State

	gameStateManager.SetInitialState(mainMenuScene);

	//// Using custom window procedure
	AESysInit(hInstance, nCmdShow, (s32)GRAPHICS::TARGET_WINDOW_WIDTH, (s32)GRAPHICS::TARGET_WINDOW_HEIGHT, 1, 60, true, NULL);
	StarBangBang::InitBasicMesh();
	
	PathFinder::PathFinderInit();
	PathFinder::ShowGrid(false);

	//Full screen
	//AESysInit(hInstance, nCmdShow, 1920, 1080, 1, 60, true, NULL);
	AEToogleFullScreen(false);

	// Changing the window title
	AESysSetWindowTitle("Captain Stealth");

	// reset the system modules
	AESysReset();

	AEGfxSetBackgroundColor(0.3f, 0.6f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	// ALWAYS CREATE FONTS OUTSIDE LOOP
	fontId = AEGfxCreateFont("./Resources/Roboto-Regular.ttf", 12);
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
		g_dt = static_cast<float>(AEFrameRateControllerGetFrameTime());

		// Handling Input
		AEInputUpdate();


		if (AEInputCheckCurr(AEVK_LALT))
		{
			if (AEInputCheckTriggered(AEVK_RETURN))
				GRAPHICS::ToggleFullscreen();
		}

		// Events
		MessageBus::Update();

		// Update State
		gameStateManager.Update();

		//Moved to gsm draw
		//StarBangBang::TestGrid();
		StarBangBang::PathFinderTest();
		CollisionManager::ResolverUpdate();
		
		DisplayFps();
		audioEngine.Update();

		//StarBangBang::Test_BoxUpdate();
		//StarbangBang::Test_CircleUpdate();
		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (!gameStateManager.GetStatus() || !AESysDoesWindowExist())
			gGameRunning = 0;
	}

	FreeUnitMeshes();
	//Audio Engine (temp implementation)
	audioEngine.ReleaseSound(sound);
	audioEngine.Exit();

	//free font
	AEGfxDestroyFont(fontId);

	//free the system
	AESysExit();


}