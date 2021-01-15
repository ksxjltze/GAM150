#pragma once
#include <AEEngine.h>
#include "Image.h"
#include <vector>

namespace TempTeam
{
	class GraphicsManager
	{
	public:
		AEGfxTexture* LoadTexture(const char* filePath);
		AEGfxVertexList* CreateMesh(float width, float height);

	private:
		std::vector<AEGfxVertexList*> meshList;
		std::vector<AEGfxTexture*> textureList;
		std::vector<Image> imageList;
	};
}