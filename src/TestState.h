#pragma once
#include "State.h"
#include "AEEngine.h"

namespace TempTeam
{
	class TestState : public State
	{
	public:
		TestState();
		void Init();
		void Update();
		void Exit();
	private:
		//Mesh
		AEGfxVertexList* pMesh1 = 0;
		AEGfxVertexList* pMesh2 = 0;
		AEGfxVertexList* pMeshLine = 0;

		//Textures
		AEGfxTexture* pTex1 = 0;
		AEGfxTexture* pTex2 = 0;

		float obj1X = 0.0f, obj1Y = 0.0f; // Position variables for object 1
		float objtexX = 0, objtexY = 0; // Texture variables for object 2 and 3 texture
		float camX, camY;
		int counter = 0; // Counter to swap textures

		s8 fontId = 0;
	};

}