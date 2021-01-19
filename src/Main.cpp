// ---------------------------------------------------------------------------
// includes

#include "AEEngine.h"
#include "GameStateManager.h"
#include "TestState.h"
#include "TestState2.h"
#include "MapEditor.h"

// ---------------------------------------------------------------------------
// main

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	///////////////////////
	// Variable declaration

	int gGameRunning = 1;
	StarBangBang::GameStateManager gameStateManager;

	State* state1 = gameStateManager.AddGameState<StarBangBang::TestState>();
	State* state2 = gameStateManager.AddGameState<StarBangBang::TestState2>();
	State* state3 = gameStateManager.AddGameState<StarBangBang::MapEditor>();
	gameStateManager.SetInitialState(state1);

	// Variable declaration end
	///////////////////////////


	/////////////////
	// Initialization
	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 800, 600, 1, 60, true, NULL);

	// Changing the window title
	AESysSetWindowTitle("My New Demo!");

	// reset the system modules
	AESysReset();

	AEGfxSetBackgroundColor(0.3f, 0.6f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	//currentState->Load();
	//currentState->Init();

	// Initialization end
	/////////////////////

	// Game Loop
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

		// Update State
		gameStateManager.Update();
		//currentState->Update();
		//currentState->Draw();

		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}
	
	//currentState->Free();
	//currentState->Unload();
	// free the system
	AESysExit();
}