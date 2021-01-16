#pragma once
#include <AEEngine.h>
#include "Image.h"
#include <vector>

namespace StarBangBang
{
	class GraphicsManager
	{
	public:
		AEGfxTexture* LoadTexture(const char* filePath);
		AEGfxVertexList* CreateMesh(float width, float height);
		void UnloadTextures();
		void FreeMeshes();

	private:
		std::vector<AEGfxVertexList*> meshList;
		std::vector<AEGfxTexture*> textureList;
	};
}