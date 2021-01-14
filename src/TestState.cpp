#include "TestState.h"

using namespace TempTeam;

TestState::TestState()
{

}

void TestState::Init()
{
	////////////////////////////////
// Creating the objects (Shapes)
// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();

	// 1 triangle at a time
	// X, Y, Color, texU, texV
	AEGfxTriAdd(
		-25.5f, -25.5f, 0xFFFF0000, 0.0f, 0.0f,
		25.5f, 0.0f, 0xFFFF0000, 0.0f, 0.0f,
		-25.5f, 25.5f, 0xFFFF0000, 0.0f, 0.0f);

	// Saving the mesh (list of triangles) in pMesh1

	pMesh1 = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh1, "Failed to create mesh 1!!");

	// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();

	// This shape has 2 triangles
	AEGfxTriAdd(
		-30.0f, -30.0f, 0x00FF00FF, 0.0f, 1.0f,
		30.0f, -30.0f, 0x00FFFF00, 1.0f, 1.0f,
		-30.0f, 30.0f, 0x0000FFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		30.0f, -30.0f, 0x00FFFFFF, 1.0f, 1.0f,
		30.0f, 30.0f, 0x00FFFFFF, 1.0f, 0.0f,
		-30.0f, 30.0f, 0x00FFFFFF, 0.0f, 0.0f);

	// Saving the mesh (list of triangles) in pMesh2

	pMesh2 = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh2, "Failed to create mesh 2!!");

	// Informing the library that we're about to start adding vertices
	AEGfxMeshStart();

	// This shape has 5 vertices
	AEGfxVertexAdd(0.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxVertexAdd(100.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxVertexAdd(200.0f, 150.0f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxVertexAdd(300.0f, -100.0f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxVertexAdd(100.0f, -250.0f, 0xFFFFFFFF, 0.0f, 0.0f);


	pMeshLine = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMeshLine, "Failed to create line mesh!!");

	// Creating the objects (Shapes) end
	////////////////////////////////////



	////////////////////////////
	// Loading textures (images)
	pTex1 = AEGfxTextureLoad("../Resources/PlanetTexture.png");
	AE_ASSERT_MESG(pTex1, "Failed to create texture1!!");

	pTex2 = AEGfxTextureLoad("../Resources/YellowTexture.png");
	AE_ASSERT_MESG(pTex2, "Failed to create texture2!!");
	// Loading textures (images) end
	//////////////////////////////////

	//////////////////////////////////
	// Creating Fonts	
	fontId = AEGfxCreateFont("../Resources/Roboto-Regular.ttf", 12);
	// Creating Fonts end
	//////////////////////////////////
}

void TestState::Update()
{
	///////////////////
// Game loop update
// Blending mode
	if (AEInputCheckCurr(AEVK_1))
		AEGfxSetBlendMode(AE_GFX_BM_NONE);
	else if (AEInputCheckCurr(AEVK_2))
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	else if (AEInputCheckCurr(AEVK_3))
		AEGfxSetBlendMode(AE_GFX_BM_ADD);

	// Object 1 Control
	if (AEInputCheckCurr(AEVK_UP))
		obj1Y += 3.0f;
	else if (AEInputCheckCurr(AEVK_DOWN))
		obj1Y -= 3.0f;

	if (AEInputCheckCurr(AEVK_LEFT))
		obj1X -= 3.0f;
	else if (AEInputCheckCurr(AEVK_RIGHT))
		obj1X += 3.0f;

	// Texture offset
	if (AEInputCheckCurr(AEVK_L))
		objtexX -= 0.01f;
	else if (AEInputCheckCurr(AEVK_J))
		objtexX += 0.01f;

	if (AEInputCheckCurr(AEVK_I))
		objtexY += 0.01f;
	else if (AEInputCheckCurr(AEVK_K))
		objtexY -= 0.01f;

	AEGfxSetCamPosition(obj1X, obj1Y);

	// Game loop update end
	///////////////////////

	//////////////////
	// Game loop draw

	// Drawing object 1
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	// Set position for object 1
	AEGfxSetPosition(0.0f, 0.0f);
	// No texture for object 1
	AEGfxTextureSet(NULL, 0, 0);
	// No Tint
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Set position for object 1
	AEGfxSetPosition(obj1X, obj1Y);
	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(pMesh1, AE_GFX_MDM_TRIANGLES);

	// Drawing object 2 - (first) - No tint
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	// Set position for object 2
	AEGfxSetPosition(100.0f, -60.0f);
	// No tint
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Set texture
	//AEGfxTextureSet(pTex2, objtexX, objtexY);
	++counter;
	if (counter < 120)
		AEGfxTextureSet(pTex1, objtexX, objtexY);		// Same object, different texture
	else if (counter < 240)
		AEGfxTextureSet(pTex2, objtexX, objtexY);		// Same object, different texture
	else
	{
		AEGfxTextureSet(pTex1, objtexX, objtexY);		// Same object, different texture
		counter = 0;
	}
	// Set Transparency
	AEGfxSetTransparency(1.0f);
	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(pMesh2, AE_GFX_MDM_TRIANGLES);


	// Drawing object 3 - (Second) - Blue tint
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	// Set position for object 3
	AEGfxSetPosition(100.0f, 60.0f);
	// Add Blue tint
	AEGfxSetTintColor(0.0f, 0.0f, 1.0f, 1.0f);
	// Set texture
	//AEGfxTextureSet(pTex1, objtexX, objtexY);
	++counter;
	if (counter < 120)
		AEGfxTextureSet(pTex1, objtexX, objtexY);		// Same object, different texture
	else if (counter < 240)
		AEGfxTextureSet(pTex2, objtexX, objtexY);		// Same object, different texture
	else
	{
		AEGfxTextureSet(pTex1, objtexX, objtexY);		// Same object, different texture
		counter = 0;
	}
	// Set Transparency
	AEGfxSetTransparency(1.0f);
	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(pMesh2, AE_GFX_MDM_TRIANGLES);

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(0.0f, 0.0f);
	AEGfxMeshDraw(pMeshLine, AE_GFX_MDM_LINES_STRIP);

	char strBuffer[100];
	memset(strBuffer, 0, 100 * sizeof(char));
	sprintf_s(strBuffer, "FPS:  %.6f", AEFrameRateControllerGetFrameRate());

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	f32 TextWidth, TextHeight;
	AEGfxGetPrintSize(fontId, strBuffer, 1.0f, TextWidth, TextHeight);
	AEGfxPrint(fontId, strBuffer, 0.99 - TextWidth, 0.99 - TextHeight, 1.0f, 1.f, 1.f, 1.f);


	// Game loop draw end
	/////////////////////
}

void TestState::Exit()
{
	//Free objects and textures
	AEGfxMeshFree(pMesh1);
	AEGfxMeshFree(pMesh2);
	AEGfxMeshFree(pMeshLine);
	AEGfxTextureUnload(pTex1);
	AEGfxTextureUnload(pTex2);
	AEGfxDestroyFont(fontId);
}
