#pragma once
#include <AEEngine.h>
#include <vector>

namespace StarBangBang
{
	void DrawImage(AEGfxVertexList* mesh, AEGfxTexture* texture, AEVec2 pos);
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